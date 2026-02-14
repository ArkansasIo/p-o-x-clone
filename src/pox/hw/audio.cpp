#include "pox/hw/audio.hpp"
#include <algorithm>

namespace pox {

void Audio::reset(u32 sample_rate) {
  sample_rate_ = sample_rate;
  enabled_ = false;
  period_ = 100;
  phase_ = 0;
  volume_ = 0.2f;
  out_.clear();
}

void Audio::push_sample(float s) {
  out_.push_back(s);
  out_.push_back(s);
}

void Audio::step(u32 /*cpu_cycles*/, u32 sample_budget) {
  if (!enabled_) return;

  for (u32 i = 0; i < sample_budget; i++) {
    phase_++;
    if (phase_ >= period_) phase_ = 0;
    const float sq = (phase_ < (period_ / 2)) ? +volume_ : -volume_;
    push_sample(sq);
  }
}

u8 Audio::read_reg(u16 off) const {
  switch (off) {
    case 0x00: return enabled_ ? 1 : 0;
    case 0x01: return (u8)std::clamp<int>(int(volume_ * 255.0f), 0, 255);
    case 0x02: return (u8)(period_ & 0xFF);
    case 0x03: return (u8)((period_ >> 8) & 0xFF);
    default:   return 0;
  }
}

void Audio::write_reg(u16 off, u8 v) {
  switch (off) {
    case 0x00: enabled_ = (v & 1) != 0; break;
    case 0x01: volume_  = float(v) / 255.0f; break;
    case 0x02: period_  = (u16)((period_ & 0xFF00) | v); break;
    case 0x03: period_  = (u16)((period_ & 0x00FF) | (u16(v) << 8)); break;
    default: break;
  }
}

std::vector<float> Audio::drain_samples() {
  std::vector<float> tmp;
  tmp.swap(out_);
  return tmp;
}

} // namespace pox
