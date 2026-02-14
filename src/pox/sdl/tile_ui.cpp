// Implementation for tile pages, splash logo screen, and game start
#include "tile_ui.hpp"
#include <SDL.h>
#include <iostream>

namespace pox_sdl {

TilePage::TilePage(const std::vector<std::string>& labels) : tile_labels(labels), selected(0) {}

void TilePage::show(SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, 60, 60, 60, 255);
    SDL_RenderClear(ren);
    for (size_t i = 0; i < tile_labels.size(); ++i) {
        SDL_Rect tileRect = {80 + int(i) * 120, 180, 100, 100};
        if (int(i) == selected)
            SDL_SetRenderDrawColor(ren, 220, 180, 60, 255);
        else
            SDL_SetRenderDrawColor(ren, 120, 120, 120, 255);
        SDL_RenderFillRect(ren, &tileRect);
        // ... (draw tile label)
    }
    SDL_RenderPresent(ren);
}

void TilePage::handleInput(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) selected = (selected + 1) % tile_labels.size();
        if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) selected = (selected - 1 + tile_labels.size()) % tile_labels.size();
    }
}

void SplashLogoScreen::show(SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, 30, 30, 90, 255);
    SDL_RenderClear(ren);
    SDL_Rect logoRect = {160, 80, 320, 120};
    SDL_SetRenderDrawColor(ren, 240, 240, 80, 255);
    SDL_RenderFillRect(ren, &logoRect);
    // ... (draw logo text or image)
    SDL_RenderPresent(ren);
    SDL_Delay(1200);
}

void startGame(SDL_Renderer* ren) {
    SplashLogoScreen splash;
    splash.show(ren);
    TilePage tiles({"Adventure", "Survival", "Sandbox", "Settings"});
    bool inTiles = true;
    while (inTiles) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) inTiles = false;
            tiles.handleInput(e);
            if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                inTiles = false; // Start game mode
            }
        }
        tiles.show(ren);
        SDL_Delay(16);
    }
    // ...start main game logic here...
    std::cout << "Game mode selected!" << std::endl;
}

} // namespace pox_sdl
