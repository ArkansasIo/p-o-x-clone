// Implementation for splash screen, logo, load screen, loading bar, title, main menu, submenus, and game logic
#include "ui_framework.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

namespace pox_sdl {

void SplashScreen::show(SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, 30, 30, 60, 255);
    SDL_RenderClear(ren);
    // Draw splash text
    // ... (placeholder for logo)
    SDL_RenderPresent(ren);
    SDL_Delay(1200);
}

void Logo::render(SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, 200, 200, 40, 255);
    SDL_Rect logoRect = {120, 60, 320, 120};
    SDL_RenderFillRect(ren, &logoRect);
    // ... (draw text or image)
}

void LoadScreen::show(SDL_Renderer* ren, float progress) {
    SDL_SetRenderDrawColor(ren, 40, 40, 80, 255);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 180, 180, 220, 255);
    SDL_Rect barBg = {100, 220, 400, 40};
    SDL_RenderFillRect(ren, &barBg);
    SDL_SetRenderDrawColor(ren, 60, 180, 60, 255);
    SDL_Rect bar = {100, 220, static_cast<int>(400 * progress), 40};
    SDL_RenderFillRect(ren, &bar);
    SDL_RenderPresent(ren);
}

void TitleScreen::show(SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, 60, 60, 120, 255);
    SDL_RenderClear(ren);
    // ... (draw title text)
    SDL_RenderPresent(ren);
}

MainMenu::MainMenu() : selected(0) {
    menu_items = {"Start Game", "Load Game", "Options", "Exit"};
}

void MainMenu::show(SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, 80, 80, 80, 255);
    SDL_RenderClear(ren);
    for (size_t i = 0; i < menu_items.size(); ++i) {
        SDL_Rect itemRect = {120, 120 + int(i) * 60, 320, 40};
        if (int(i) == selected)
            SDL_SetRenderDrawColor(ren, 180, 220, 240, 255);
        else
            SDL_SetRenderDrawColor(ren, 120, 120, 120, 255);
        SDL_RenderFillRect(ren, &itemRect);
        // ... (draw menu text)
    }
    SDL_RenderPresent(ren);
}

void MainMenu::handleInput(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) selected = (selected + 1) % menu_items.size();
        if (e.key.keysym.scancode == SDL_SCANCODE_UP) selected = (selected - 1 + menu_items.size()) % menu_items.size();
    }
}

SubMenu::SubMenu(const std::vector<std::string>& items) : submenu_items(items), selected(0) {}

void SubMenu::show(SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, 100, 100, 100, 255);
    SDL_RenderClear(ren);
    for (size_t i = 0; i < submenu_items.size(); ++i) {
        SDL_Rect itemRect = {160, 120 + int(i) * 50, 240, 36};
        if (int(i) == selected)
            SDL_SetRenderDrawColor(ren, 220, 180, 240, 255);
        else
            SDL_SetRenderDrawColor(ren, 140, 140, 140, 255);
        SDL_RenderFillRect(ren, &itemRect);
        // ... (draw submenu text)
    }
    SDL_RenderPresent(ren);
}

void SubMenu::handleInput(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) selected = (selected + 1) % submenu_items.size();
        if (e.key.keysym.scancode == SDL_SCANCODE_UP) selected = (selected - 1 + submenu_items.size()) % submenu_items.size();
    }
}

void runGameLoop(SDL_Renderer* ren) {
    SplashScreen splash;
    splash.show(ren);
    Logo logo;
    logo.render(ren);
    SDL_RenderPresent(ren);
    SDL_Delay(800);
    LoadScreen loader;
    for (int i = 0; i <= 100; ++i) {
        loader.show(ren, i / 100.0f);
        SDL_Delay(10);
    }
    TitleScreen title;
    title.show(ren);
    SDL_Delay(1200);
    MainMenu menu;
    bool inMenu = true;
    bool running = true;
    while (running) {
        // Main menu loop
        while (inMenu) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) { inMenu = false; running = false; }
                menu.handleInput(e);
                if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    if (menu.selected == 0) { inMenu = false; /* Start Game */ }
                    else if (menu.selected == 1) { // Load Game
                        std::vector<std::string> slots = {"Slot 1", "Slot 2", "Slot 3", "Back"};
                        SubMenu loadMenu(slots);
                        bool inSub = true;
                        while (inSub) {
                            SDL_Event sube;
                            while (SDL_PollEvent(&sube)) {
                                if (sube.type == SDL_QUIT) { inSub = false; running = false; }
                                loadMenu.handleInput(sube);
                                if (sube.type == SDL_KEYDOWN && (sube.key.keysym.scancode == SDL_SCANCODE_ESCAPE || sube.key.keysym.scancode == SDL_SCANCODE_RETURN)) {
                                    if (loadMenu.selected == 3 || sube.key.keysym.scancode == SDL_SCANCODE_ESCAPE) inSub = false; // Back
                                    else if (sube.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                                        std::cout << "[Menu] Load slot: " << loadMenu.submenu_items[loadMenu.selected] << std::endl;
                                        // TODO: Add actual load logic here
                                    }
                                }
                            }
                            loadMenu.show(ren);
                            SDL_Delay(16);
                        }
                    }
                    else if (menu.selected == 2) { // Options
                        std::vector<std::string> opts = {"Audio", "Video", "Controls", "Back"};
                        SubMenu optMenu(opts);
                        bool inSub = true;
                        while (inSub) {
                            SDL_Event sube;
                            while (SDL_PollEvent(&sube)) {
                                if (sube.type == SDL_QUIT) { inSub = false; running = false; }
                                optMenu.handleInput(sube);
                                if (sube.type == SDL_KEYDOWN && (sube.key.keysym.scancode == SDL_SCANCODE_ESCAPE || sube.key.keysym.scancode == SDL_SCANCODE_RETURN)) {
                                    if (optMenu.selected == 3 || sube.key.keysym.scancode == SDL_SCANCODE_ESCAPE) inSub = false; // Back
                                    else if (sube.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                                        std::cout << "[Menu] Option selected: " << optMenu.submenu_items[optMenu.selected] << std::endl;
                                        // TODO: Add actual option logic here
                                    }
                                }
                            }
                            optMenu.show(ren);
                            SDL_Delay(16);
                        }
                    }
                    else if (menu.selected == 3) { inMenu = false; running = false; /* Exit */ }
                }
            }
            menu.show(ren);
            SDL_Delay(16);
        }
        if (running) {
            // ...start main game logic here...
            std::cout << "Game started!" << std::endl;
            running = false; // For now, exit after starting game
        }
    }
}

} // namespace pox_sdl
