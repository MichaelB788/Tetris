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
      tetris.unpause_game();
    break;

  case Tetris::State::Running:
    // Check for pause, highest priority
    if (is_key_pressed(SDL_SCANCODE_SPACE)) {
      tetris.pause_game();
      for (auto &act : repeatable_actions) {
        act.input_delay.reset();
        act.periodic_func.reset();
      }
      break; // Don't process any other events after pausing
    }

    // Handle repeatable actions
    for (auto &[scancode, input_delay, periodic_func] : repeatable_actions) {
      if (is_key_pressed(scancode)) {
        input_delay.reset();
        periodic_func.invoke_early();
      } else if (is_key_held(scancode)) {
        if (input_delay.has_set_off())
          periodic_func.tick(delta);
        else
          input_delay.tick(delta);
      } else if (is_key_released(scancode)) {
        input_delay.reset();
        periodic_func.reset();
      }
    }

    // Handle one-shot moves
    if (is_key_pressed(SDL_SCANCODE_W))
      tetris.player_hard_drop();
    else if (is_key_pressed(SDL_SCANCODE_UP))
      tetris.hold_current_piece();
    else if (is_key_pressed(SDL_SCANCODE_DOWN))
      tetris.player_rotate_half();
    else if (is_key_pressed(SDL_SCANCODE_LEFT))
      tetris.player_rotate_ccw();
    else if (is_key_pressed(SDL_SCANCODE_RIGHT))
      tetris.player_rotate_cw();
    break;
  }

  // Keep a copy of the current keyboard for later
  std::copy_n(curr_keyboard, SDL_SCANCODE_COUNT, prev_keyboard);

  return AppResult::Continue;
}
