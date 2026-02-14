#pragma once
#include <SDL.h>
#include <vector>

namespace pox_sdl {

// Minimal audio output stub.
// This scaffold does not attempt perfect audio sync; it just shows how to wire it.
struct AudioOut {
  SDL_AudioDeviceID dev = 0;
  SDL_AudioSpec spec{};

  bool init(int sample_rate);
  void shutdown();

  // push interleaved stereo float samples [-1..1]
  void queue_f32(const std::vector<float>& samples);
};

} // namespace pox_sdl
