#include "zone_renderer.hpp"
#include <SDL.h>

namespace pox {
namespace ui {

ZoneRenderer::ZoneRenderer(SDL_Renderer* renderer) : renderer_(renderer) {}

void ZoneRenderer::render(const pox::game::ZoneSystem& zoneSys, int x, int y) {
    // Example: Render current zone name and description
    const auto& zone = zoneSys.get_current_zone();
    SDL_Rect zoneRect = {x, y, 300, 60};
    SDL_SetRenderDrawColor(renderer_, 60, 160, 60, 255);
    SDL_RenderFillRect(renderer_, &zoneRect);
}

} // namespace ui
} // namespace pox
