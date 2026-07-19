#include "AppState.hpp"
#include <SDL3/SDL_init.h>
#include <thread>

auto AppState::update_frame() -> SDL_AppResult {
  frame_start = std::chrono::steady_clock::now();
  const auto delta_time = frame_start - prev_frame_start;
  prev_frame_start = frame_start;

  auto result = handle_keyboard_input();
  tick(delta_time);
  renderer.render_frame(tetris);

  const auto elapsed = std::chrono::steady_clock::now() - frame_start;
  if (elapsed < fps.get_frame_duration()) {
    std::this_thread::sleep_for(fps.get_frame_duration() - elapsed);
  }

  return result;
}

auto AppState::handle_keyboard_input() -> SDL_AppResult {
  const auto keyboard = SDL_GetKeyboardState(nullptr);
  switch (tetris.get_state()) {
    using enum Tetris::State;
  case Running:
    handler.handle_game_events(tetris, keyboard);
    break;
  case Paused:
    handler.handle_paused_events(tetris, keyboard);
    break;
  case GameOver:
    return handler.handle_game_over_events(tetris, keyboard);
    break;
  }
  return SDL_APP_CONTINUE;
}

void AppState::tick(std::chrono::nanoseconds delta) {
  if (tetris.get_state() == Tetris::State::Running) {
    tetris.tick(delta);
    handler.tick(tetris, delta);
  }
}

void AppState::handle_window_resize_event() {
  renderer.center_frame_within_window();
}
