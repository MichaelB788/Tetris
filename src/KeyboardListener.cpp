#include "KeyboardListener.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <algorithm>
#include <chrono>
#include <functional>

auto KeyboardListener::process_keystrokes(Tetris &tetris,
                                          std::chrono::nanoseconds delta)
    -> AppResult {
  const auto curr_keyboard = SDL_GetKeyboardState(nullptr);

  auto is_key_pressed = [&](SDL_Scancode sc) -> bool {
    return !prev_keyboard[sc] && curr_keyboard[sc];
  };
  auto is_key_held = [&](SDL_Scancode sc) -> bool {
    return prev_keyboard[sc] && curr_keyboard[sc];
  };
  auto is_key_released = [&](SDL_Scancode sc) -> bool {
    return prev_keyboard[sc] && !curr_keyboard[sc];
  };

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
    // Handle one-shot moves; block other input by breaking out early
    if (is_key_pressed(SDL_SCANCODE_SPACE)) {
      tetris.pause_game();
      for (auto &act : repeatable_actions) {
        act.input_delay.reset();
        act.repeat_delay.reset();
      }
      break;
    }
    if (is_key_pressed(SDL_SCANCODE_W)) {
      tetris.player_hard_drop();
      break;
    }
    if (is_key_pressed(SDL_SCANCODE_UP)) {
      tetris.hold_current_piece();
      break;
    }

    // Handle one-shot moves
    if (is_key_pressed(SDL_SCANCODE_LEFT))
      tetris.player_rotate_counterclockwise();
    else if (is_key_pressed(SDL_SCANCODE_RIGHT))
      tetris.player_rotate_clockwise();

    // Handle repeatable actions
    for (auto &[scancode, input_delay, repeat_delay, handler] :
         repeatable_actions) {
      if (is_key_pressed(scancode)) {
        std::invoke(handler, tetris);
      } else if (is_key_held(scancode)) {
        if (input_delay.has_set_off()) {
          if (repeat_delay.tick(delta); repeat_delay.has_set_off()) {
            std::invoke(handler, tetris);
            repeat_delay.reset();
          }
        } else {
          input_delay.tick(delta);
        }
      } else if (is_key_released(scancode)) {
        input_delay.reset();
        repeat_delay.reset();
      }
    }
    break;
  }

  std::copy_n(curr_keyboard, SDL_SCANCODE_COUNT, prev_keyboard);
  return AppResult::Continue;
}
