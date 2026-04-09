#include "core/TetrisApp.hpp"
#include "SDL3/SDL_render.h"
#include "platform/PlatformSDL.hpp"
#include "util/Timer.hpp"
#include <SDL3/SDL_events.h>
#include <chrono>
#include <iostream>
#include <thread>

void TetrisApp::run() {
  // FPS cap recorded in nanoseconds. Uses integer division.
  const std::chrono::nanoseconds FPS_CAP{1'000'000'000 / target_fps_};

#ifndef NDEBUG
  // Variables used for logging FPS
  int frame_count = 0;
  Timer log_frame = {.duration = std::chrono::seconds(1)};
#endif

  // Start of game loop
  auto prev_time{std::chrono::steady_clock::now()};
  while (running_) {
    // Compute delta and update previous time point
    const auto curr_time = std::chrono::steady_clock::now();
    const auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(
        curr_time - prev_time);
    prev_time = curr_time;

    // Poll events and update game state
    poll_events();
    tetris_.update(delta);

    // Handle keyboard input AFTER polling events
    handler_.handle_kb_input(delta);

    handle_tetris_state();

    render_frame();

#ifndef NDEBUG
    // Log FPS in debug
    if (log_frame.elapsed >= log_frame.duration) {
      std::cout << frame_count << "\n";
      log_frame.elapsed = {};
      frame_count = 0;
    } else {
      log_frame.elapsed += delta;
      ++frame_count;
    }
#endif

    // If frame finished early, sleep for remainder of time
    const auto frame_time = std::chrono::steady_clock::now() - curr_time;
    if (frame_time < FPS_CAP) {
      std::this_thread::sleep_for(FPS_CAP - frame_time);
    }
  }
}

void TetrisApp::poll_events() {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_EVENT_QUIT:
      running_ = false;
      break;
    case SDL_EVENT_WINDOW_RESIZED: {
      auto &[w, h] = win_size_;
      SDL_GetWindowSizeInPixels(window_.get(), &w, &h);
      center_within_window();
    } break;
    default:
      break;
    }
  }
}

void TetrisApp::render_frame() {
  SDL_SetRenderDrawColor(renderer_.get(), 0x17, 0x18, 0x28, 0xFF);
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
