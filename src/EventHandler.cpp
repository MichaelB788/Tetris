#include "EventHandler.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_keyboard.h>
#include <cassert>
#include <chrono>
#include <cstddef>

void EventHandler::listen_to_keyboard_input() {
  // Handle current keyboard inputs
  const auto curr_keyboard = SDL_GetKeyboardState(nullptr);
  for (const auto &command : controls) {
    const auto scancode = command.scancode;
    const auto event = command.event;
    if (!prev_keyboard[scancode] && curr_keyboard[scancode]) {
      pending_new_events |= event;
    } else if (prev_keyboard[scancode] && curr_keyboard[scancode]) {
      pending_held_events |= event;
    } else if (prev_keyboard[scancode] && !curr_keyboard[scancode]) {
      pending_held_events &= ~event;
    }
  }

  // Take a snapshot of current keyboard state
  for (size_t i = 0; i < SDL_SCANCODE_COUNT; ++i) {
    prev_keyboard[i] = curr_keyboard[i];
  }
}

auto EventHandler::find_command_from_event(Event event) -> Command & {
  for (auto &command : controls) {
    if (command.event == event) {
      return command;
    }
  }
  assert(false);
}

void EventHandler::handle_new_events() {
  for (size_t bit_idx = 0; bit_idx < controls.size(); ++bit_idx) {
    const auto event = static_cast<Event>(1 << bit_idx);
    if (pending_new_events & event) {
      handle_event(event);

      if (auto &command = find_command_from_event(event);
          command.timer.has_value()) {
        command.timer->init_delay.reset();
        command.timer->repeat_interval.reset();
      }
    }
  }
  pending_new_events = 0;
}

void EventHandler::handle_repeated_events(std::chrono::nanoseconds delta) {
  for (size_t bit_idx = 0; bit_idx < controls.size(); ++bit_idx) {
    const auto event = static_cast<Event>(1 << bit_idx);
    if (pending_held_events & event) {
      if (auto &command = find_command_from_event(event);
          command.timer.has_value()) {
        command.timer->init_delay.invoke_when_elapsed(delta, [&] {
          command.timer->repeat_interval.invoke_periodically(
              delta, [&] { handle_event(event); });
        });
      }
    }
  }
}

void EventHandler::handle_pause_event() {
  if (pending_new_events & TOGGLE_PAUSE_CMD) {
    tetris.unpause();
    pending_new_events = 0;
    pending_held_events = 0;

    for (auto &command : controls) {
      if (command.timer.has_value()) {
        command.timer->init_delay.reset();
        command.timer->repeat_interval.reset();
      }
    }
  }
}

void EventHandler::handle_event(Event command) {
  switch (command) {
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
    break;
  }
}
