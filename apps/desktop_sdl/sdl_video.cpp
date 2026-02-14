#include "sdl_video.hpp"
#include <cstdio>

namespace pox_sdl {

bool Video::init(const char* title, int w_, int h_, int scale) {
  w = w_; h = h_;
  win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         w * scale, h * scale, SDL_WINDOW_SHOWN);
  if (!win) return false;

  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  if (!ren) return false;

  tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
  if (!tex) return false;

  return true;
}

void Video::shutdown() {
  if (tex) SDL_DestroyTexture(tex);
  if (ren) SDL_DestroyRenderer(ren);
  if (win) SDL_DestroyWindow(win);
  tex = nullptr; ren = nullptr; win = nullptr;
}

void Video::present_rgba(const uint32_t* rgba, int w_, int h_) {
  SDL_UpdateTexture(tex, nullptr, rgba, w_ * (int)sizeof(uint32_t));
  SDL_RenderClear(ren);
  SDL_RenderCopy(ren, tex, nullptr, nullptr);
  SDL_RenderPresent(ren);
}

} // namespace pox_sdl
