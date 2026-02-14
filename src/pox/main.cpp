// Full game main loop and integration
#include "pox/sdl/tile_ui.hpp"
#include "pox/sdl/ui_framework.hpp"
#include "pox/game/game_logic.hpp"
#include "pox/game/main_character.hpp"
#include <SDL.h>
#include <iostream>

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
        std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Window* win = SDL_CreateWindow("POX Clone Full Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) {
        std::cout << "Renderer creation failed" << std::endl;
        SDL_Quit();
        return 1;
    }

    // Splash logo screen
    pox_sdl::SplashLogoScreen splash;
    splash.show(ren);

    // Tile page for mode selection
    pox_sdl::TilePage tiles({"Adventure", "Survival", "Sandbox", "Settings"});
    bool inTiles = true;
    while (inTiles) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) inTiles = false;
            tiles.handleInput(e);
            if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                inTiles = false;
            }
        }
        tiles.show(ren);
        SDL_Delay(16);
    }

    // Main menu
    pox_sdl::MainMenu menu;
    bool inMenu = true;
    while (inMenu) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) inMenu = false;
            menu.handleInput(e);
            if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                if (menu.selected == 0) inMenu = false; // Start Game
                if (menu.selected == 3) inMenu = false; // Exit
            }
        }
        menu.show(ren);
        SDL_Delay(16);
    }

    // Game logic
    pox::game::GameLogic game;
    game.generateProceduralWorld();
    game.spawnCreature("Hero");
    game.spawnCreature("Monster");
    pox::game::MainCharacter player;
    player.setName("POX");
    game.addPlayer(player);
    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            // ...handle input, update game state...
        }
        game.tick();
        // ...render, update GUI...
        SDL_SetRenderDrawColor(ren, 40, 40, 80, 255);
        SDL_RenderClear(ren);
        // ...draw game state...
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
