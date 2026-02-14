#include "pox/pox.hpp"
#include "pox/log.hpp"
#include "pox/core/bus.hpp"
#include "pox/core/clock.hpp"
#include "pox/hw/cpu8.hpp"
#include "pox/hw/memory.hpp"
#include "pox/hw/display.hpp"
#include "pox/hw/input.hpp"
#include "pox/hw/timer.hpp"
#include "pox/hw/audio.hpp"
#include "pox/hw/power.hpp"
#include "pox/hw/cartridge.hpp"
#include "pox/debug/trace.hpp"
#include "pox/debug/debugger.hpp"
#include "pox/core/events.hpp"
#include "pox/util/fileio.hpp"
#include <filesystem>

namespace pox {

struct Machine::Impl {
  Config cfg;
  Clock clock;

  Memory mem;
  Display lcd;
  Input input;
  Timer timer;
  Audio audio;
  Power power;
  Cartridge cart;

  Bus bus;
  CPU8 cpu;

  Framebuffer fb;
  AudioBuffer ab;

  std::vector<u8> bootrom;

  debug::TraceBuffer trace;
  debug::Debugger dbg;
  EventFlags events;

  Impl(Config c)
  : cfg(std::move(c))
  , clock(cfg.cpu_hz, cfg.frame_hz, cfg.sample_rate)
  , lcd(cfg.lcd_w, cfg.lcd_h)
  , bus(mem, lcd, input, timer, audio, power, cart)
  , cpu(bus)
  {
    fb.w = cfg.lcd_w; fb.h = cfg.lcd_h;
    fb.rgba.resize(size_t(fb.w) * size_t(fb.h), 0xFF000000u);

    mem.reset();
    timer.reset();
    audio.reset(cfg.sample_rate);
    power.reset();

    trace.enable(cfg.enable_trace);
    dbg.set_enabled(cfg.enable_debugger);

    std::filesystem::create_directories(std::filesystem::path(cfg.save_prefix).parent_path());
  }
};

Machine::Machine(Config cfg) : impl_(std::make_unique<Impl>(std::move(cfg))) {}
Machine::~Machine() = default;

bool Machine::load_bootrom(const std::string& path) {
  impl_->bootrom = util::read_file(path);
  return !impl_->bootrom.empty();
}

bool Machine::load_cartridge(const std::string& path) {
  return impl_->cart.load(path, impl_->cfg.save_prefix);
}

bool Machine::save_sram() {
  return impl_->cart.save_sram();
}

void Machine::reset() {
  impl_->mem.reset();
  impl_->timer.reset();
  impl_->audio.reset(impl_->cfg.sample_rate);
  impl_->power.reset();
  impl_->events.clear_all();

  // TODO: when you know reset vector: read from ROM header/bootrom.
  impl_->cpu.reset(0x0000);
}

void Machine::set_buttons(uint16_t mask) {
  impl_->input.set_buttons(mask);
}

void Machine::run_frame() {
  const u64 budget = impl_->clock.begin_frame_budget();
  const u64 start_cycles = impl_->cpu.state().cycles;

  while ((impl_->cpu.state().cycles - start_cycles) < budget) {
    // Debugger stops (scaffold)
    if (impl_->dbg.enabled()) {
      if (impl_->dbg.is_breakpoint(impl_->cpu.state().pc) || impl_->dbg.single_step()) {
        log::warn("Debugger stop at PC=0x%04X", impl_->cpu.state().pc);
        break;
      }
    }

    // Trace snapshot BEFORE executing
    if (impl_->trace.enabled()) {
      debug::TraceEntry te;
      te.cycle = impl_->cpu.state().cycles;
      te.pc = impl_->cpu.state().pc;
      te.a = impl_->cpu.state().a;
      te.x = impl_->cpu.state().x;
      te.y = impl_->cpu.state().y;
      te.sp = impl_->cpu.state().sp;
      te.flags = impl_->cpu.state().flags;
      te.opcode = impl_->bus.read8(te.pc); // peek
      impl_->trace.push(te);
    }

    const u32 c = impl_->cpu.step();

    // Step peripherals
    impl_->timer.step(c);
    const u32 samples = impl_->clock.samples_for_cycles(c);
    impl_->audio.step(c, samples);

    // Raise placeholder IRQ events
    if (impl_->timer.poll_timer_irq()) impl_->events.raise(Event::TimerIRQ);

    // In a real emulator: CPU checks events and vectors to handler
    // once interrupt wiring is confirmed.
  }

  impl_->clock.end_frame_budget(impl_->cpu.state().cycles - start_cycles);

  // Render LCD
  impl_->lcd.render_from_vram(impl_->mem.vram_data(), Memory::VRAM_SIZE);
  impl_->fb.rgba = impl_->lcd.framebuffer_rgba();

  // Audio out
  impl_->ab.samples = impl_->audio.drain_samples();
}

const Framebuffer& Machine::framebuffer() const { return impl_->fb; }
const AudioBuffer& Machine::audio() const { return impl_->ab; }
uint64_t Machine::cycles() const { return impl_->cpu.state().cycles; }

} // namespace pox
