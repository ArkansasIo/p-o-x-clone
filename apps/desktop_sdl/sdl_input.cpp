#include "sdl_input.hpp"
#include "pox/types.hpp"

namespace pox_sdl {

uint16_t read_buttons() {
  const Uint8* ks = SDL_GetKeyboardState(nullptr);
  uint16_t m = 0;
  if (ks[SDL_SCANCODE_UP])    m |= pox::BTN_UP;
  if (ks[SDL_SCANCODE_DOWN])  m |= pox::BTN_DOWN;
  if (ks[SDL_SCANCODE_LEFT])  m |= pox::BTN_LEFT;
  if (ks[SDL_SCANCODE_RIGHT]) m |= pox::BTN_RIGHT;
  if (ks[SDL_SCANCODE_Z])     m |= pox::BTN_A;
  if (ks[SDL_SCANCODE_X])     m |= pox::BTN_B;
  if (ks[SDL_SCANCODE_RETURN])m |= pox::BTN_START;
  if (ks[SDL_SCANCODE_RSHIFT])m |= pox::BTN_SELECT;
  return m;
}

} // namespace pox_sdl
