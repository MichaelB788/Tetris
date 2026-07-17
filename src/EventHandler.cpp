#include "EventHandler.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_keyboard.h>
#include <cassert>
#include <chrono>
#include <cstddef>

void EventHandler::listen_to_keyboard_input() {
  // Handle current keyboard inputs
  const auto curr_keyboard = SDL_GetKeyboardState(nullptr);
  for (const auto &command : controls_) {
    const auto scancode = command.scancode;
    const auto event = command.event;
    if (!prev_keyboard_[scancode] && curr_keyboard[scancode]) {
      pending_new_events_ |= event;
    } else if (prev_keyboard_[scancode] && curr_keyboard[scancode]) {
      pending_held_events_ |= event;
    } else if (prev_keyboard_[scancode] && !curr_keyboard[scancode]) {
      pending_new_events_ &= ~event;
      pending_held_events_ &= ~event;
    }
  }

  // Take a snapshot of current keyboard state
  for (size_t i = 0; i < SDL_SCANCODE_COUNT; ++i) {
    prev_keyboard_[i] = curr_keyboard[i];
  }
}

auto EventHandler::idx_of_event(Event event) const -> int {
  for (int i = 0; i < controls_.size(); ++i) {
    if (controls_[i].event == event) {
      return i;
    }
  }
  assert(false);
}

void EventHandler::handle_new_events(Tetris &tetris) {
  for (size_t bit_idx = 0; bit_idx < controls_.size(); ++bit_idx) {
    const auto event = static_cast<Event>(1 << bit_idx);
    if (pending_new_events_ & event) {
      handle_event(event, tetris);

      if (const auto i = idx_of_event(event); controls_[i].timer.has_value()) {
        controls_[i].timer->init_delay.reset();
        controls_[i].timer->repeat_interval.reset();
      }
    }
  }
  pending_new_events_ = 0;
}

void EventHandler::handle_repeated_events(Tetris &tetris,
                                          std::chrono::nanoseconds delta) {
  for (size_t bit_idx = 0; bit_idx < controls_.size(); ++bit_idx) {
    const auto event = static_cast<Event>(1 << bit_idx);
    if (pending_held_events_ & event) {
      if (const auto i = idx_of_event(event); controls_[i].timer.has_value()) {
        controls_[i].timer->init_delay.invoke_when_elapsed(delta, [&] {
          controls_[i].timer->repeat_interval.invoke_periodically(
              delta, [&] { handle_event(event, tetris); });
        });
      }
    }
  }
}

void EventHandler::handle_event(Event command, Tetris &tetris) {
  if (command == TOGGLE_PAUSE_CMD) {
    tetris.toggle_pause();
    pending_new_events_ = 0;
    pending_held_events_ = 0;
    return;
  }

  if (tetris.get_state() == Tetris::State::Paused) {
    return;
  }

  switch (command) {
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
  default:
    break;
  }
}
