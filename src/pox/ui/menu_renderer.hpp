#pragma once
#include <SDL.h>
#include "pox/game/menu_text.hpp"

namespace pox {
namespace ui {

class MenuRenderer {
public:
    MenuRenderer(SDL_Renderer* renderer);
    void render(const pox::game::MenuTextSystem& menuTextSys, int x, int y);
private:
    SDL_Renderer* renderer_;
};

} // namespace ui
} // namespace pox
