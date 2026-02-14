#pragma once
#include "creature_record.hpp"
#include <cstdint>

namespace pox::game {

class CreatureRuntime {
public:
    CreatureRuntime(CreatureRecord& rec);
    void tick(); // Simulate one time step (age, hunger, etc)
    void feed();
    void play();
    void heal();
    // Add more actions as needed
private:
    CreatureRecord& rec_;
    uint32_t age_ = 0;
    uint8_t hunger_ = 0;
    uint8_t mood_ = 0;
};

} // namespace pox::game
