#include "core/TetrisApp.hpp"
#include "SDL3/SDL_render.h"
#include "platform/PlatformSDL.hpp"
#include <chrono>
#include <iostream>
#include <thread>

void TetrisApp::run() {
  using nano = std::chrono::nanoseconds;
  using milli = std::chrono::milliseconds;
  using clock = std::chrono::steady_clock;

  const nano FPS_CAP{1'000'000'000 / target_fps_};
  int frame_count = 0;

  auto prev_time{clock::now()};

#ifndef NDEBUG
  nano accumulator{0};
#endif

  while (running_) {
    const auto curr_time = clock::now();
    const auto delta = curr_time - prev_time;
    prev_time = curr_time;

    tetris_.update(std::chrono::duration_cast<milli>(delta));
    handle_events();
    center_within_window();
    handle_tetris_state();
    render_frame();

#ifndef NDEBUG
    accumulator += delta;
    ++frame_count;
    if (accumulator >= std::chrono::seconds(1)) {
      std::cout << frame_count << "\n";
      accumulator = milli::zero();
      frame_count = 0;
    }
#endif

    const auto frame_time = clock::now() - curr_time;
    if (frame_time < FPS_CAP) {
      std::this_thread::sleep_for(FPS_CAP - frame_time);
    }
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
    default:
      break;
    }
  }

  handler_.handle_kb_input();
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
