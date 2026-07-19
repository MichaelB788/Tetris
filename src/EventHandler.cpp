#include "EventHandler.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keyboard.h>
#include <cassert>
#include <chrono>

void EventHandler::handle_game_events(Tetris &tetris,
                                      const bool *curr_keyboard) {
  for (auto &command : controls) {
    if (!prev_keyboard[command.scancode] && curr_keyboard[command.scancode]) {
      execute_command(tetris, command);
      if (command.timer.has_value()) {
        command.timer->init_delay.reset();
        command.timer->repeat_interval.reset();
      }
    } else if (prev_keyboard[command.scancode] &&
               curr_keyboard[command.scancode]) {
      pending_held_events |= command.event;
    } else if (prev_keyboard[command.scancode] &&
               !curr_keyboard[command.scancode]) {
      pending_held_events &= ~command.event;
    }

    prev_keyboard[command.scancode] = curr_keyboard[command.scancode];
  }
}

void EventHandler::handle_paused_events(Tetris &tetris,
                                        const bool *curr_keyboard) {
  for (auto &command : controls) {
    if (command.event == TOGGLE_PAUSE_CMD) {
      if (!prev_keyboard[command.scancode] && curr_keyboard[command.scancode]) {
        tetris.unpause();
        pending_held_events = 0;
      }
      prev_keyboard[command.scancode] = curr_keyboard[command.scancode];
    }
  }
}

auto EventHandler::handle_game_over_events(Tetris &tetris,
                                           const bool *curr_keyboard)
    -> SDL_AppResult {
  if (curr_keyboard[SDL_SCANCODE_Y]) {
    tetris.reset();
  } else if (curr_keyboard[SDL_SCANCODE_N]) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

void EventHandler::tick(Tetris &tetris, std::chrono::nanoseconds delta) {
  for (auto &command : controls) {
    if ((pending_held_events & command.event) && command.timer.has_value()) {
      command.timer->init_delay.invoke_when_elapsed(delta, [&] {
        command.timer->repeat_interval.invoke_periodically(
            delta, [&] { execute_command(tetris, command); });
      });
    }
  }
}

void EventHandler::execute_command(Tetris &tetris, Command &command) {
  switch (command.event) {
  case NULL_CMD:
    break;
  case MOVE_LEFT_CMD:
    tetris.move_left();
    break;
  case MOVE_RIGHT_CMD:
    tetris.move_right();
    break;
  case SOFT_DROP_CMD:
    tetris.soft_drop();
    break;
  case HARD_DROP_CMD:
    tetris.hard_drop();
    break;
  case ROTATE_CW_CMD:
    tetris.rotate_cw();
    break;
  case ROTATE_CCW_CMD:
    tetris.rotate_ccw();
    break;
  case ROTATE_HALF_CMD:
    tetris.rotate_half();
    break;
  case HOLD_ACTIVE_CMD:
    tetris.hold_active();
    break;
  case TOGGLE_PAUSE_CMD:
    tetris.pause();
    for (auto &command : controls) {
      prev_keyboard[command.scancode] = false;
    }
    break;
  }
}
