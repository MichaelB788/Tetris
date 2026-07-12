#include "EventHandler.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_keyboard.h>
#include <chrono>
#include <random>

void EventHandler::handle_kb_input(Tetris &tetris, std::mt19937 &rng,
                                   std::chrono::nanoseconds delta) {
  // Handle current keyboard inputs
  const auto curr_kb_state = SDL_GetKeyboardState(nullptr);
  for (const auto &[scancode, command] : controls_) {
    if (!prev_kb_state_[scancode] && curr_kb_state[scancode]) {
      handle_first_key_press(tetris, command, rng);
    } else if (prev_kb_state_[scancode] && curr_kb_state[scancode]) {
      handle_key_down(tetris, command, rng, delta);
    }
  }

  // Take a snapshot of current keyboard state
  for (size_t i = 0; i < SDL_SCANCODE_COUNT; ++i) {
    prev_kb_state_[i] = curr_kb_state[i];
  }
}

void EventHandler::handle_first_key_press(Tetris &tetris,
                                          Tetris::Command command,
                                          std::mt19937 &rng) {
  tetris.handle_command(command, rng);
  movement_.init_delay.reset();
  rotation_.init_delay.reset();
}

void EventHandler::handle_key_down(Tetris &tetris, Tetris::Command command,
                                   std::mt19937 &rng,
                                   std::chrono::nanoseconds delta) {
  using enum Tetris::Command;
  auto execute_input = [&] { tetris.handle_command(command, rng); };
  if (command == RotateClockwise || command == RotateCounterclockwise ||
      command == RotateHalf) {
    rotation_.init_delay.invoke_when_elapsed(delta, [&] {
      rotation_.repeat_interval.invoke_periodically(delta, execute_input);
    });
  } else {
    movement_.init_delay.invoke_when_elapsed(delta, [&] {
      movement_.repeat_interval.invoke_periodically(delta, execute_input);
    });
  }
}
