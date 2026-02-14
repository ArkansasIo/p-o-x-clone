#include "pox/game/creature_runtime.hpp"

namespace pox::game {

CreatureRuntime::CreatureRuntime(CreatureRecord& rec) : rec_(rec) {}

void CreatureRuntime::tick() {
    ++age_;
    if (hunger_ < 255) ++hunger_;
    if (hunger_ > 200 && rec_.head_hp > 0) --rec_.head_hp;
    if (mood_ > 0) --mood_;
}

void CreatureRuntime::feed() {
    if (hunger_ > 10) hunger_ -= 10;
    mood_ += 5;
}

void CreatureRuntime::play() {
    mood_ += 10;
    hunger_ += 5;
}

void CreatureRuntime::heal() {
    if (rec_.head_hp < 100) ++rec_.head_hp;
}

} // namespace pox::game
