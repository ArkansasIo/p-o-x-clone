#include "sdl_audio.hpp"
#include <cstdio>

namespace pox_sdl {

bool AudioOut::init(int sample_rate) {
  SDL_AudioSpec want{};
  want.freq = sample_rate;
  want.format = AUDIO_F32;
  want.channels = 2;
  want.samples = 1024;
  want.callback = nullptr;

  dev = SDL_OpenAudioDevice(nullptr, 0, &want, &spec, 0);
  if (!dev) return false;
  SDL_PauseAudioDevice(dev, 0);
  return true;
}

void AudioOut::shutdown() {
  if (dev) {
    SDL_CloseAudioDevice(dev);
    dev = 0;
  }
}

void AudioOut::queue_f32(const std::vector<float>& samples) {
  if (!dev || samples.empty()) return;
  SDL_QueueAudio(dev, samples.data(), (Uint32)(samples.size() * sizeof(float)));
}

} // namespace pox_sdl
