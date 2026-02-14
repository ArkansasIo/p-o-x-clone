#pragma once
#include <SDL.h>
#include <string>
#include "pox/game/zones.hpp"

namespace pox {
namespace ui {

class ZoneRenderer {
public:
    ZoneRenderer(SDL_Renderer* renderer);
    void render(const pox::game::ZoneSystem& zoneSys, int x, int y);
private:
    SDL_Renderer* renderer_;
};

} // namespace ui
} // namespace pox
