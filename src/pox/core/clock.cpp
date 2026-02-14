#include "pox/core/clock.hpp"

namespace pox {

Clock::Clock(uint32_t cpu_hz, uint32_t frame_hz, uint32_t sample_rate)
: cpu_hz_(cpu_hz), frame_hz_(frame_hz), sample_rate_(sample_rate) {
  cpf_ = cpu_hz_ / frame_hz_;
  rem_step_ = cpu_hz_ % frame_hz_;
  rem_ = 0;
}

uint32_t Clock::samples_for_cycles(uint32_t cycles) const {
  return (uint64_t(cycles) * uint64_t(sample_rate_)) / uint64_t(cpu_hz_);
}

uint64_t Clock::begin_frame_budget() {
  uint64_t budget = cpf_;
  rem_ += rem_step_;
  if (rem_ >= frame_hz_) {
    rem_ -= frame_hz_;
    budget += 1;
  }
  return budget;
}

void Clock::end_frame_budget(uint64_t /*cycles_used*/) {}

} // namespace pox
