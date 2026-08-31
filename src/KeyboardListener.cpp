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
  switch (tetris.get_state()) {
  case Tetris::State::GameOver:
    if (curr_keyboard[SDL_SCANCODE_Y])
      tetris.reset();
    else if (curr_keyboard[SDL_SCANCODE_N])
      return AppResult::Quit;
    break;
  case Tetris::State::Paused:
    if (!prev_keyboard[SDL_SCANCODE_SPACE] && curr_keyboard[SDL_SCANCODE_SPACE])
      tetris.unpause();
    break;
  case Tetris::State::Running:
    // Check for pause, highest priority
    if (!prev_keyboard[SDL_SCANCODE_SPACE] &&
        curr_keyboard[SDL_SCANCODE_SPACE]) {
      tetris.pause();
      break;
    }

    // Handle inputs which can be repeated
    for (auto &act : actions) {
      if (!prev_keyboard[act.scancode] && curr_keyboard[act.scancode])
        act.func.invoke_early();
      else if (prev_keyboard[act.scancode] && curr_keyboard[act.scancode])
        act.func.tick(delta);
      else if (prev_keyboard[act.scancode] && !curr_keyboard[act.scancode])
        act.func.reset();
    }

    // Handle inputs with no repeat
    if (curr_keyboard[SDL_SCANCODE_UP])
      tetris.hold_active();
    break;
  }

  std::copy_n(curr_keyboard, SDL_SCANCODE_COUNT, prev_keyboard);
  return AppResult::Continue;
}
