#include "menu_renderer.hpp"
#include <SDL.h>
#include <SDL_ttf.h>

namespace pox {
namespace ui {

MenuRenderer::MenuRenderer(SDL_Renderer* renderer) : renderer_(renderer) {}

void MenuRenderer::render(const pox::game::MenuTextSystem& menuTextSys, int x, int y) {
    // Example: Render menu zone title and options
    // NOTE: Requires SDL_ttf for text rendering
    // Stub: Draw rectangles for options
    const auto& zone = menuTextSys.get_current_zone();
    SDL_Rect titleRect = {x, y, 300, 40};
    SDL_SetRenderDrawColor(renderer_, 80, 80, 160, 255);
    SDL_RenderFillRect(renderer_, &titleRect);
    // Draw options
    int optY = y + 50;
    for (size_t i = 0; i < zone.options.size(); ++i) {
        SDL_Rect optRect = {x, optY, 300, 30};
        SDL_SetRenderDrawColor(renderer_, 120, 120, 200, 255);
        SDL_RenderFillRect(renderer_, &optRect);
        optY += 40;
    }
}

} // namespace ui
} // namespace pox
