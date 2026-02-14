#pragma once
#include <SDL.h>
#include <cstdint>
#include <vector>

namespace pox_sdl {

struct Video {
  SDL_Window* win = nullptr;
  SDL_Renderer* ren = nullptr;
  SDL_Texture* tex = nullptr;
  int w = 0;
  int h = 0;

  bool init(const char* title, int w, int h, int scale);
  void shutdown();

  void present_rgba(const uint32_t* rgba, int w, int h);
};

} // namespace pox_sdl
