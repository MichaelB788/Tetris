#include "core/TetrisApp.hpp"
#include "SDL3/SDL_render.h"
#include "platform/PlatformSDL.hpp"
#include "util/Point.hpp"
#include "util/Timer.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include <chrono>
#include <iostream>
#include <thread>

static constexpr float PIXEL_SCALE = 32;

TetrisApp::TetrisApp(const Specification &spec)
    : target_fps_(spec.target_fps),
      tetris_renderer_(*renderer_, spec.tetromino_atlas, PIXEL_SCALE),
      text_renderer_(*renderer_, spec.font_path, PIXEL_SCALE),
      handler_(spec.controls) {
  tetris_renderer_.fit_within_window(*window_);
}

void TetrisApp::run() {
  // FPS cap recorded in nanoseconds. Uses integer division.
  const std::chrono::nanoseconds FPS_CAP{1'000'000'000 / target_fps_};

#ifndef NDEBUG
  // Variables used for logging FPS
  int frame_count = 0;
  Timer log_frame{std::chrono::seconds(1)};
#endif

  // Start of game loop
  while (running_) {
    // Compute delta and update previous time point
    curr_time = std::chrono::steady_clock::now();
    const auto delta = curr_time - prev_time;
    prev_time = curr_time;

    // Poll events and update game state
    {
      SDL_Event event;

      while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
          running_ = false;
          break;
        case SDL_EVENT_WINDOW_RESIZED:
          tetris_renderer_.fit_within_window(*window_);
          break;
        default:
          break;
        }
      }
    }
    handler_.handle_kb_input(tetris_, rng_, delta);
    tetris_.update(delta, rng_);
    handle_tetris_state();

    render_frame();

#ifndef NDEBUG
    // Log FPS in debug
    if (!log_frame.has_elapsed())
      ++frame_count;
    log_frame.invoke_periodically(delta, [&] {
      std::cout << frame_count << "\n";
      frame_count = 0;
    });
#endif

    // If frame finished early, sleep for remainder of time
    const auto frame_time = std::chrono::steady_clock::now() - curr_time;
    if (frame_time < FPS_CAP) {
      std::this_thread::sleep_for(FPS_CAP - frame_time);
    }
  }
}

void TetrisApp::render_frame() {
  SDL_SetRenderDrawColor(renderer_.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(renderer_.get());

  tetris_renderer_.draw_snapshot(*renderer_, tetris_.snapshot());

  // Render screen text
  {
    const auto hud_layout = tetris_renderer_.compute_hud_layout();
    text_renderer_.render_text("NEXT", hud_layout.next_label);
    text_renderer_.render_text("HOLD", hud_layout.hold_label);
    text_renderer_.render_text("SCORE", hud_layout.score_label);
    text_renderer_.render_int(tetris_.score(), hud_layout.score_value);
  }

  SDL_RenderPresent(renderer_.get());
}

void TetrisApp::handle_tetris_state() {
  if (tetris_.game_over())
    tetris_ = Tetris{rng_};
}
