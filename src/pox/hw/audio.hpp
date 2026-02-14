// Audio header for boot animation SFX
#pragma once
#include <vector>

namespace pox {

class Audio {
public:
    void reset(unsigned int sample_rate);
    void push_sample(float s);
    void step(unsigned int cpu_cycles, unsigned int sample_budget);
    unsigned char read_reg(unsigned short off) const;
    void write_reg(unsigned short off, unsigned char v);
    std::vector<float> drain_samples();
    bool enabled_;
    unsigned int sample_rate_;
    unsigned int period_;
    unsigned int phase_;
    float volume_;
    std::vector<float> out_;
};

} // namespace pox
