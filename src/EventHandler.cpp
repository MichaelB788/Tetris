#include "EventHandler.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_keyboard.h>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <random>

void EventHandler::listen_to_keyboard_input() {
  // Handle current keyboard inputs
  const auto curr_keyboard = SDL_GetKeyboardState(nullptr);
  for (const auto &control : controls_) {
    const auto scancode = control.scancode;
    const auto command = control.command;
    if (!prev_keyboard_[scancode] && curr_keyboard[scancode]) {
      pending_new_events_ |= command;
    } else if (prev_keyboard_[scancode] && curr_keyboard[scancode]) {
      pending_held_events_ |= command;
    } else if (prev_keyboard_[scancode] && !curr_keyboard[scancode]) {
      pending_new_events_ &= ~command;
      pending_held_events_ &= ~command;
    }
  }

  // Take a snapshot of current keyboard state
  for (size_t i = 0; i < SDL_SCANCODE_COUNT; ++i) {
    prev_keyboard_[i] = curr_keyboard[i];
  }
}

auto EventHandler::idx_of_command(Command command) const -> int {
  for (int i = 0; i < controls_.size(); ++i) {
    if (controls_[i].command == command) {
      return i;
    }
  }
  assert(false);
}

void EventHandler::handle_new_events(Tetris &tetris, std::mt19937 &rng) {
  for (size_t bit_idx = 0; bit_idx < controls_.size(); ++bit_idx) {
    const auto cmd = static_cast<Command>(1 << bit_idx);
    if (pending_new_events_ & cmd) {
      pending_new_events_ &= ~cmd;
      handle_command(cmd, tetris, rng);

      if (const auto i = idx_of_command(cmd); controls_[i].timer.has_value()) {
        controls_[i].timer->init_delay.reset();
        controls_[i].timer->repeat_interval.reset();
      }
    }
  }
}

void EventHandler::handle_repeated_events(Tetris &tetris, std::mt19937 &rng,
                                          std::chrono::nanoseconds delta) {
  for (size_t bit_idx = 0; bit_idx < controls_.size(); ++bit_idx) {
    const auto cmd = static_cast<Command>(1 << bit_idx);
    if (pending_held_events_ & cmd) {
      if (const auto i = idx_of_command(cmd); controls_[i].timer.has_value()) {
        controls_[i].timer->init_delay.invoke_when_elapsed(delta, [&] {
          controls_[i].timer->repeat_interval.invoke_periodically(
              delta, [&] { handle_command(cmd, tetris, rng); });
        });
      }
    }
  }
}

void EventHandler::handle_command(Command command, Tetris &tetris,
                                  std::mt19937 &rng) {
  if (command == TOGGLE_PAUSE_CMD) {
    tetris.toggle_pause();
    pending_new_events_ = 0;
    pending_held_events_ = 0;
    return;
  }

  if (tetris.get_state() == Tetris::State::Paused) {
    return;
  }

  // clang-format off
  switch (command) {
    case NULL_CMD: break;
    case MOVE_LEFT_CMD: tetris.move_left(); break;
    case MOVE_RIGHT_CMD: tetris.move_right(); break;
    case SOFT_DROP_CMD: tetris.soft_drop(); break;
    case HARD_DROP_CMD: tetris.hard_drop(rng); break;
    case ROTATE_CW_CMD: tetris.rotate_cw(); break;
    case ROTATE_CCW_CMD: tetris.rotate_ccw(); break;
    case ROTATE_HALF_CMD: tetris.rotate_half(); break;
    case HOLD_ACTIVE_CMD: tetris.hold_active(rng); break;
    case TOGGLE_PAUSE_CMD: break;
    // clang-format on
  }
}
