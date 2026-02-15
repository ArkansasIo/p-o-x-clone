#pragma once
#include <SDL.h>
#include "pox/game/settings.hpp"

namespace pox {
namespace ui {

class SettingsRenderer {
public:
    SettingsRenderer(SDL_Renderer* renderer);
    void render(const pox::game::SettingsSystem& settingsSys, int x, int y);
private:
    SDL_Renderer* renderer_;
};

} // namespace ui
} // namespace pox
