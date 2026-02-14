// Full game main loop and integration
#include "pox/sdl/tile_ui.hpp"
#include "pox/sdl/ui_framework.hpp"
#include "pox/game/game_logic.hpp"
#include "pox/game/main_character.hpp"
#include "pox/game/menu_text.hpp"
#include "pox/game/zones.hpp"
#include "pox/game/settings.hpp"
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

    // Initialize menu text system
    pox::game::MenuTextSystem menuTextSys;
    menuTextSys.add_zone({"Main Menu", { {"Start Game", true}, {"Options", true}, {"Exit", true} }]);
    menuTextSys.add_zone({"Settings", { {"Audio", true}, {"Video", true}, {"Controls", true} }});
    menuTextSys.set_zone(0);

    // Initialize zone system
    pox::game::ZoneSystem zoneSys;
    zoneSys.add_zone({"Forest", "A lush green forest.", true});
    zoneSys.add_zone({"Desert", "A hot sandy desert.", false});
    zoneSys.add_zone({"Mountain", "A cold rocky mountain.", false});

    // Initialize settings system
    pox::game::SettingsSystem settingsSys;
    settingsSys.set("volume", "80");
    settingsSys.set("resolution", "640x480");
    settingsSys.set("difficulty", "normal");

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
            // Example: handle menu navigation
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
                    menuTextSys.set_option(menuTextSys.current_option - 1);
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                    menuTextSys.set_option(menuTextSys.current_option + 1);
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    // Example: select menu option
                    auto opt = menuTextSys.get_current_option();
                    if (opt.label == "Start Game") {
                        // Start gameplay
                        zoneSys.set_zone(0); // Enter Forest
                    }
                    if (opt.label == "Options") {
                        menuTextSys.set_zone(1); // Go to Settings
                    }
                    if (opt.label == "Exit") {
                        running = false;
                    }
                }
            }
        }
        game.tick();
        SDL_SetRenderDrawColor(ren, 40, 40, 80, 255);
        SDL_RenderClear(ren);
        // Example: render menu text
        auto zone = menuTextSys.get_current_zone();
        // Render zone.title and options (stub)
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
