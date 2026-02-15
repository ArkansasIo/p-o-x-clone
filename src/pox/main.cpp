// Full game main loop and integration
#include "pox/sdl/tile_ui.hpp"
#include "pox/sdl/ui_framework.hpp"
#include "pox/game/game_logic.hpp"
#include "pox/game/main_character.hpp"
#include "pox/game/menu_text.hpp"
#include "pox/game/zones.hpp"
#include "pox/game/settings.hpp"
#include <SDL.h>
#include <SDL_scancode.h>
#include "pox/game/kingdoms.hpp"
using pox::game::initialize_kingdoms;
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
    pox::game::initialize_kingdoms(kingdomSys);
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
    // Save slot state
    bool showSaveSlots = false;
    int selectedSlot = 0;
    const int numSlots = 3;
    std::string slotLabels[numSlots] = {"Slot 1", "Slot 2", "Slot 3"};
    bool loadingProfile = false;
    // Slot file paths and status
    std::string slotFiles[numSlots] = {"pox_save_slot1.sav", "pox_save_slot2.sav", "pox_save_slot3.sav"};
    bool slotOccupied[numSlots] = {false, false, false};
    auto checkSlots = [&]() {
        for (int i = 0; i < numSlots; ++i) {
            FILE* f = fopen(slotFiles[i].c_str(), "rb");
            slotOccupied[i] = (f != nullptr);
            if (f) fclose(f);
        }
    };
    checkSlots();

    // Example stub data to save/load
    struct SaveData {
        int dummyValue = 42;
        char name[16] = "Player";
    };
    SaveData currentSave;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN) {
                if (showSaveSlots) {
                    if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
                        selectedSlot = (selectedSlot + numSlots - 1) % numSlots;
                    }
                    if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                        selectedSlot = (selectedSlot + 1) % numSlots;
                    }
                    if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                        // Save or load logic for selectedSlot
                        if (loadingProfile) {
                            FILE* f = fopen(slotFiles[selectedSlot].c_str(), "rb");
                            if (f) {
                                fread(&currentSave, sizeof(SaveData), 1, f);
                                fclose(f);
                                std::cout << "Loaded profile from " << slotLabels[selectedSlot] << ": name=" << currentSave.name << ", value=" << currentSave.dummyValue << std::endl;
                            } else {
                                std::cout << "No save found in " << slotLabels[selectedSlot] << std::endl;
                            }
                        } else {
                            // Save stub data
                            FILE* f = fopen(slotFiles[selectedSlot].c_str(), "wb");
                            if (f) {
                                fwrite(&currentSave, sizeof(SaveData), 1, f);
                                fclose(f);
                                std::cout << "Saved new game to " << slotLabels[selectedSlot] << std::endl;
                            } else {
                                std::cout << "Failed to save to " << slotLabels[selectedSlot] << std::endl;
                            }
                        }
                        checkSlots();
                        showSaveSlots = false;
                        loadingProfile = false;
                        // Proceed to game loop or load profile data
                    }
                    if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        showSaveSlots = false;
                        loadingProfile = false;
                    }
                } else {
                    if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
                        menuTextSys.set_option(menuTextSys.current_option - 1);
                    }
                    if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                        menuTextSys.set_option(menuTextSys.current_option + 1);
                    }
                    if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                        auto opt = menuTextSys.get_current_option();
                        if (opt.label == "Start Game") {
                            showSaveSlots = true;
                            loadingProfile = false;
                            selectedSlot = 0;
                        }
                        if (opt.label == "Options") {
                            menuTextSys.set_zone(1);
                        }
                        if (opt.label == "Exit") {
                            running = false;
                        }
                    }
                    if (e.key.keysym.scancode == SDL_SCANCODE_L) {
                        // Example: Press 'L' to load a profile
                        showSaveSlots = true;
                        loadingProfile = true;
                        selectedSlot = 0;
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(ren, 40, 40, 80, 255);
        SDL_RenderClear(ren);
        if (showSaveSlots) {
            // Render save slot selection
            for (int i = 0; i < numSlots; ++i) {
                SDL_Rect slotRect = {200, 100 + i * 60, 240, 50};
                if (i == selectedSlot) {
                    SDL_SetRenderDrawColor(ren, 200, 200, 80, 255);
                } else {
                    SDL_SetRenderDrawColor(ren, 120, 120, 120, 255);
                }
                SDL_RenderFillRect(ren, &slotRect);
                // Render slot label and status (stub: rectangles, add text rendering as needed)
                // For now, print to console for demonstration
                std::string status = slotOccupied[i] ? "Occupied" : "Empty";
                if (i == selectedSlot) {
                    std::cout << "> " << slotLabels[i] << " - " << status << std::endl;
                }
            }
        } else {
            menuRenderer.render(menuTextSys, 20, 20);
            zoneRenderer.render(zoneSys, 340, 20);
            settingsRenderer.render(settingsSys, 20, 300);
        }
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
