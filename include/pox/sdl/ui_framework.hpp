// Splash screen, logo, load screen, loading bar, title, main menu, submenus, and game logic integration
#pragma once
#include <SDL.h>
#include <string>
#include <vector>

namespace pox_sdl {

class SplashScreen {
public:
    void show(SDL_Renderer* ren);
};

class Logo {
public:
    void render(SDL_Renderer* ren);
};

class LoadScreen {
public:
    void show(SDL_Renderer* ren, float progress);
};

class TitleScreen {
public:
    void show(SDL_Renderer* ren);
};

class MainMenu {
public:
    std::vector<std::string> menu_items;
    int selected;
    MainMenu();
    void show(SDL_Renderer* ren);
    void handleInput(const SDL_Event& e);
};

class SubMenu {
public:
    std::vector<std::string> submenu_items;
    int selected;
    SubMenu(const std::vector<std::string>& items);
    void show(SDL_Renderer* ren);
    void handleInput(const SDL_Event& e);
};

// Game logic integration
void runGameLoop(SDL_Renderer* ren);

} // namespace pox_sdl
