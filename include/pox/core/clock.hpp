#pragma once
#include <cstdint>

namespace pox {

class Clock {
public:
  Clock(uint32_t cpu_hz, uint32_t frame_hz, uint32_t sample_rate);

  uint64_t cycles_per_frame() const { return cpf_; }
  uint32_t samples_for_cycles(uint32_t cycles) const;

  uint64_t begin_frame_budget();
  void end_frame_budget(uint64_t cycles_used);

private:
  uint32_t cpu_hz_ = 0;
  uint32_t frame_hz_ = 0;
  uint32_t sample_rate_ = 0;

  uint64_t cpf_ = 0;
  uint64_t rem_ = 0;
  uint64_t rem_step_ = 0;
};

} // namespace pox
