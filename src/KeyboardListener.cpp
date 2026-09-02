#include "KeyboardListener.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <algorithm>
#include <cassert>
#include <chrono>

auto KeyboardListener::process_input(std::chrono::nanoseconds delta)
    -> AppResult {
  auto curr_keyboard = SDL_GetKeyboardState(0);

  auto is_key_pressed = [&](SDL_Scancode sc) -> bool {
    return !prev_keyboard[sc] && curr_keyboard[sc];
  };
  auto is_key_held = [&](SDL_Scancode sc) -> bool {
    return prev_keyboard[sc] && curr_keyboard[sc];
  };
  auto is_key_released = [&](SDL_Scancode sc) -> bool {
    return prev_keyboard[sc] && !curr_keyboard[sc];
  };

  // Handle different input based on the current state of the game
  switch (tetris.get_state()) {
  case Tetris::State::GameOver:
    if (is_key_pressed(SDL_SCANCODE_Y))
      tetris.reset();
    else if (is_key_pressed(SDL_SCANCODE_N))
      return AppResult::Quit;
    break;

  case Tetris::State::Paused:
    if (is_key_pressed(SDL_SCANCODE_SPACE))
      tetris.unpause();
    break;

  case Tetris::State::Running:
    // Check for pause, highest priority
    if (is_key_pressed(SDL_SCANCODE_SPACE)) {
      tetris.pause();
      break;
    }

    // Handle inputs which can be repeated
    for (auto &act : actions) {
      if (is_key_pressed(act.scancode)) {
        act.input_delay.reset();
        act.func.invoke_early();
      } else if (is_key_held(act.scancode)) {
        act.input_delay.tick(delta);
        if (act.input_delay.has_set_off())
          act.func.tick(delta);
      } else if (is_key_released(act.scancode)) {
        act.input_delay.reset();
        act.func.reset();
      }
    }

    // Handle inputs with no repeat
    if (is_key_pressed(SDL_SCANCODE_UP))
      tetris.hold_active();
    break;
  }

  // Keep a copy of the current keyboard for later
  std::copy_n(curr_keyboard, SDL_SCANCODE_COUNT, prev_keyboard);

  return AppResult::Continue;
}
