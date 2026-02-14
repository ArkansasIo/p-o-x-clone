#pragma once
#include "pox/types.hpp"
#include <vector>

namespace pox {

class Audio {
public:
  void reset(u32 sample_rate);

  void step(u32 cpu_cycles, u32 sample_budget);

  u8  read_reg(u16 off) const;
  void write_reg(u16 off, u8 v);

  std::vector<float> drain_samples();

private:
  u32 sample_rate_ = 44100;

  bool enabled_ = false;
  u16 period_ = 100;
  u16 phase_ = 0;
  float volume_ = 0.2f;

  std::vector<float> out_;

  void push_sample(float s);
};

} // namespace pox
