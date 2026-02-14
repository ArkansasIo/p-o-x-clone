#include "settings_renderer.hpp"
#include <SDL.h>

namespace pox {
namespace ui {

SettingsRenderer::SettingsRenderer(SDL_Renderer* renderer) : renderer_(renderer) {}

void SettingsRenderer::render(const pox::game::SettingsSystem& settingsSys, int x, int y) {
    // Example: Render settings as rectangles
    int setY = y;
    for (const auto& pair : settingsSys.settings) {
        SDL_Rect setRect = {x, setY, 300, 30};
        SDL_SetRenderDrawColor(renderer_, 200, 200, 80, 255);
        SDL_RenderFillRect(renderer_, &setRect);
        setY += 40;
    }
}

} // namespace ui
} // namespace pox
