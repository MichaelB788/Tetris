#include "AppState.hpp"
#include <thread>

void AppState::listen_to_keyboard_input() {
  handler_.listen_to_keyboard_input();
}

void AppState::tick() {
  prev_time_ = curr_time_;
  curr_time_ = std::chrono::steady_clock::now();
  const auto delta = curr_time_ - prev_time_;

  fps_counter_.tick(delta);

  if (tetris_.get_state() == Tetris::State::Running) {
    tetris_.tick(delta, rng_);
    handler_.handle_repeated_events(tetris_, rng_, delta);
  }
}

void AppState::handle_tetris_state() {
  switch (tetris_.get_state()) {
    using enum Tetris::State;
  case Running:
  case Paused:
    handler_.handle_new_events(tetris_, rng_);
    break;
  case GameOver: // TODO: Add option to continue/quit
    tetris_.reset(rng_);
    break;
    break;
  }
}

void AppState::render_frame() { app_renderer_.render_frame(tetris_); }

void AppState::sleep_thread() const {
  const auto frame_time = std::chrono::steady_clock::now() - curr_time_;
  const auto frame_duration = fps_.get_frame_duration();
  if (frame_time < frame_duration) {
    std::this_thread::sleep_for(frame_duration - frame_time);
  }
}

void AppState::handle_window_resize_event() {
  app_renderer_.center_frame_within_window();
}
