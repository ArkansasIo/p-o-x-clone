#include "pox/pox.hpp"
#include "pox/log.hpp"
#include "sdl_video.hpp"
#include "sdl_input.hpp"
#include "sdl_audio.hpp"
#include <SDL.h>
#include <cstdio>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::printf("Usage: pox_desktop <rom_or_poxr>\n");
    return 1;
  }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
    std::printf("SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  pox::log::set_config({pox::log::Level::Info, true, true, ""});

  pox::Config cfg;
  cfg.enable_trace = false;
  cfg.enable_debugger = false;
  cfg.save_prefix = "saves/pox_save";

  pox::Machine m(cfg);
  if (!m.load_cartridge(argv[1])) {
    std::printf("Failed to load ROM: %s\n", argv[1]);
    SDL_Quit();
    return 1;
  }
  m.reset();

  pox_sdl::Video video;
  if (!video.init("PO-X Clone (Scaffold)", cfg.lcd_w, cfg.lcd_h, 4)) {
    std::printf("Video init failed\n");
    SDL_Quit();
    return 1;
  }

  pox_sdl::AudioOut audio;
  audio.init(cfg.sample_rate);

  bool running = true;
  const uint32_t frame_ms = 1000 / cfg.frame_hz;

  while (running) {
    const uint32_t t0 = SDL_GetTicks();

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) running = false;
      if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) running = false;
    }

    m.set_buttons(pox_sdl::read_buttons());
    m.run_frame();

    const auto& fb = m.framebuffer();
    video.present_rgba(fb.rgba.data(), fb.w, fb.h);

    const auto& ab = m.audio();
    audio.queue_f32(ab.samples);

    const uint32_t dt = SDL_GetTicks() - t0;
    if (dt < frame_ms) SDL_Delay(frame_ms - dt);
  }

  // Persist save RAM
  m.save_sram();

  audio.shutdown();
  video.shutdown();
  SDL_Quit();
  return 0;
}
