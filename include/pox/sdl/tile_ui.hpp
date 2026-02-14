// Tile pages, splash logo screen, and game integration
#pragma once
#include <SDL.h>
#include <string>
#include <vector>

namespace pox_sdl {

class TilePage {
public:
    std::vector<std::string> tile_labels;
    int selected;
    TilePage(const std::vector<std::string>& labels);
    void show(SDL_Renderer* ren);
    void handleInput(const SDL_Event& e);
};

class SplashLogoScreen {
public:
    void show(SDL_Renderer* ren);
};

void startGame(SDL_Renderer* ren);

} // namespace pox_sdl
