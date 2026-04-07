#include "core/TetrisApp.hpp"
#include "SDL3/SDL_render.h"
#include "platform/PlatformSDL.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_surface.h>
#include <thread>

void TetrisApp::run() {
  using namespace std::chrono_literals;
  while (running_) {
    tetris_.tick();
    handle_events();
    center_within_window();
    handle_tetris_state();
    render_frame();
    std::this_thread::sleep_for(12ms);
  }
}

void TetrisApp::handle_events() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_EVENT_QUIT:
      running_ = false;
      break;
    case SDL_EVENT_WINDOW_RESIZED: {
      auto &[w, h] = win_size_;
      SDL_GetWindowSizeInPixels(window_.get(), &w, &h);
    } break;
    case SDL_EVENT_KEY_DOWN:
      handler_.handle_kb_input(e);
      break;
    default:
      break;
    }
  }
}

void TetrisApp::render_frame() {
  static const auto [r, g, b, a] = SDL_Color(0x17, 0x18, 0x28, 0xFF);
  SDL_SetRenderDrawColor(renderer_.get(), r, g, b, a);
  SDL_RenderClear(renderer_.get());

  tetris_renderer_.draw_frame(tetris_, *renderer_);
  text_renderer_.render_screen_text();
  text_renderer_.render_score_int(tetris_.score());

  SDL_RenderPresent(renderer_.get());
}

void TetrisApp::handle_tetris_state() {
  if (tetris_.status() == Status::GameOver)
    reset();
}

void TetrisApp::center_within_window() {
  tetris_renderer_.align_inside_rect(win_size_);
  text_renderer_.align_with_game(tetris_renderer_);
}
