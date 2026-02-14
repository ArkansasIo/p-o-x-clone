// Full game main loop and integration
#include "pox/sdl/tile_ui.hpp"
#include "pox/sdl/ui_framework.hpp"
#include "pox/game/game_logic.hpp"
#include "pox/game/main_character.hpp"
#include "pox/game/menu_text.hpp"
#include "pox/game/zones.hpp"
#include "pox/game/settings.hpp"
#include "pox/game/kingdoms.hpp"
#include "pox/game/continents.hpp"
#include "pox/game/rpg_systems.hpp"
#include "pox/ui/menu_renderer.hpp"
#include "pox/ui/zone_renderer.hpp"
#include "pox/ui/settings_renderer.hpp"
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

    // Initialize all systems
    pox::game::MenuTextSystem menuTextSys;
    menuTextSys.add_zone({"Main Menu", { {"Start Game", true}, {"Options", true}, {"Exit", true} }});
    menuTextSys.add_zone({"Settings", { {"Audio", true}, {"Video", true}, {"Controls", true} }});
    menuTextSys.set_zone(0);

    pox::game::ZoneSystem zoneSys;
    pox::game::KingdomSystem kingdomSys;
    initialize_kingdoms(kingdomSys);
    pox::game::WorldMap worldMap;
    worldMap.initialize();
    pox::game::SettingsSystem settingsSys;
    settingsSys.set("volume", "80");
    settingsSys.set("resolution", "640x480");
    settingsSys.set("difficulty", "normal");
    pox::game::RPGSystems rpgSys;
    rpgSys.initialize();

    // UI renderers
    pox::ui::MenuRenderer menuRenderer(ren);
    pox::ui::ZoneRenderer zoneRenderer(ren);
    pox::ui::SettingsRenderer settingsRenderer(ren);

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
                    menuTextSys.set_option(menuTextSys.current_option - 1);
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                    menuTextSys.set_option(menuTextSys.current_option + 1);
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    auto opt = menuTextSys.get_current_option();
                    if (opt.label == "Start Game") {
                        zoneSys.set_zone(0);
                    }
                    if (opt.label == "Options") {
                        menuTextSys.set_zone(1);
                    }
                    if (opt.label == "Exit") {
                        running = false;
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(ren, 40, 40, 80, 255);
        SDL_RenderClear(ren);
        menuRenderer.render(menuTextSys, 20, 20);
        zoneRenderer.render(zoneSys, 340, 20);
        settingsRenderer.render(settingsSys, 20, 300);
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
