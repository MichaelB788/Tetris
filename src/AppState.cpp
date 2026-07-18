#include "AppState.hpp"
#include <thread>

auto AppState::update_frame() -> SDL_AppResult {
  SDL_AppResult result;

  prev_time = curr_time;
  curr_time = std::chrono::steady_clock::now();

  result = handler.listen_to_keyboard_input();
  tick(curr_time - prev_time);
  handle_tetris_state();
  renderer.render_frame(tetris);

  const auto frame_time = std::chrono::steady_clock::now() - curr_time;
  const auto frame_duration = fps.get_frame_duration();
  if (frame_time < frame_duration) {
    std::this_thread::sleep_for(frame_duration - frame_time);
  }

  return result;
}

void AppState::tick(std::chrono::nanoseconds delta) {
  if (tetris.get_state() == Tetris::State::Running) {
    tetris.tick(delta);
    handler.handle_repeated_events(delta);
  }
}

void AppState::handle_tetris_state() {
  switch (tetris.get_state()) {
    using enum Tetris::State;
  case Running:
    handler.handle_new_events();
    break;
  case Paused:
    handler.handle_pause_event();
    break;
  case GameOver:
    break;
  }
}

void AppState::handle_window_resize_event() {
  renderer.center_frame_within_window();
}
