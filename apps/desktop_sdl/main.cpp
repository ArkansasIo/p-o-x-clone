#include "pox/pox.hpp"
#include "pox/log.hpp"
#include "sdl_video.hpp"
#include "sdl_input.hpp"
#include "sdl_audio.hpp"
#include <SDL.h>
#include <cstdio>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::printf("Usage: pox_desktop <rom_or_poxr>\n");
    return 1;
  }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
    std::printf("SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  pox::log::set_config({pox::log::Level::Info, true, true, ""});

  pox::Config cfg;
  cfg.enable_trace = false;
  cfg.enable_debugger = false;
  cfg.save_prefix = "saves/pox_save";

  std::printf("[DEBUG] Attempting to load ROM: %s\n", argv[1]);
  pox::Machine m(cfg);
  bool loaded = m.load_cartridge(argv[1]);
  std::printf("[DEBUG] ROM load result: %d\n", loaded);
  if (!loaded) {
    std::printf("Failed to load ROM: %s\n", argv[1]);
    SDL_Quit();
    return 1;
  }
  m.reset();

  pox_sdl::Video video;
  if (!video.init("PO-X Clone (Scaffold)", cfg.lcd_w, cfg.lcd_h, 4)) {
    std::printf("Video init failed\n");
    SDL_Quit();
    return 1;
  }

  pox_sdl::AudioOut audio;
  audio.init(cfg.sample_rate);

  bool running = true;
  const uint32_t frame_ms = 1000 / cfg.frame_hz;

  // GUI button rectangles
  SDL_Rect gui_buttons[2] = {
    {20, 20, 120, 40}, // GUI Button
    {160, 20, 120, 40} // PI Button
  };
  const char* gui_labels[2] = {"GUI", "PI Interface"};
  int gui_button_hover = -1;
  bool pi_panel_visible = false;

  while (running) {
    const uint32_t t0 = SDL_GetTicks();

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) running = false;
      if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) running = false;
      if (e.type == SDL_MOUSEMOTION) {
        gui_button_hover = -1;
        for (int i = 0; i < 2; ++i) {
          if (e.motion.x >= gui_buttons[i].x && e.motion.x < gui_buttons[i].x + gui_buttons[i].w &&
              e.motion.y >= gui_buttons[i].y && e.motion.y < gui_buttons[i].y + gui_buttons[i].h) {
            gui_button_hover = i;
          }
        }
      }
      if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        for (int i = 0; i < 2; ++i) {
          if (e.button.x >= gui_buttons[i].x && e.button.x < gui_buttons[i].x + gui_buttons[i].w &&
              e.button.y >= gui_buttons[i].y && e.button.y < gui_buttons[i].y + gui_buttons[i].h) {
            std::printf("[INFO] %s button pressed\n", gui_labels[i]);
            if (i == 1) pi_panel_visible = !pi_panel_visible;
          }
        }
      }
    }

    m.set_buttons(pox_sdl::read_buttons());
    m.run_frame();

    const auto& fb = m.framebuffer();
    video.present_rgba(fb.rgba.data(), fb.w, fb.h);

    // Draw GUI and PI buttons overlay
    SDL_Renderer* ren = video.ren;
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    for (int i = 0; i < 2; ++i) {
      if (gui_button_hover == i)
        SDL_SetRenderDrawColor(ren, 200, 200, 255, 180);
      else
        SDL_SetRenderDrawColor(ren, 180, 180, 180, 180);
      SDL_RenderFillRect(ren, &gui_buttons[i]);
      SDL_SetRenderDrawColor(ren, 60, 60, 60, 255);
      SDL_RenderDrawRect(ren, &gui_buttons[i]);
    }

    // PI interface panel overlay
    if (pi_panel_visible) {
      SDL_Rect pi_panel = {320, 20, 240, 180};
      SDL_SetRenderDrawColor(ren, 100, 180, 220, 220);
      SDL_RenderFillRect(ren, &pi_panel);
      SDL_SetRenderDrawColor(ren, 40, 80, 120, 255);
      SDL_RenderDrawRect(ren, &pi_panel);
      // Placeholder controls: 2 rectangles for PI actions
      SDL_Rect pi_btn1 = {340, 50, 200, 40};
      SDL_Rect pi_btn2 = {340, 110, 200, 40};
      SDL_SetRenderDrawColor(ren, 180, 220, 240, 200);
      SDL_RenderFillRect(ren, &pi_btn1);
      SDL_RenderFillRect(ren, &pi_btn2);
      SDL_SetRenderDrawColor(ren, 40, 80, 120, 255);
      SDL_RenderDrawRect(ren, &pi_btn1);
      SDL_RenderDrawRect(ren, &pi_btn2);
      // Print to console for demo
      std::printf("[PI PANEL] Displayed PI interface controls\n");
    }
    SDL_RenderPresent(ren);

    // Debug: print framebuffer summary
    int nonblack = 0;
    for (size_t i = 0; i < fb.rgba.size(); ++i) {
      if (fb.rgba[i] != 0xFF000000u) ++nonblack;
    }
    if (nonblack == 0) {
      std::printf("[DEBUG] Framebuffer is all black\n");
    } else {
      std::printf("[DEBUG] Framebuffer has %d non-black pixels\n", nonblack);
    }

    const auto& ab = m.audio();
    audio.queue_f32(ab.samples);

    const uint32_t dt = SDL_GetTicks() - t0;
    if (dt < frame_ms) SDL_Delay(frame_ms - dt);
  }

  // Persist save RAM
  m.save_sram();

  audio.shutdown();
  video.shutdown();
  SDL_Quit();
  return 0;
}
