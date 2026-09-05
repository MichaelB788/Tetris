#pragma once
#include "PeriodicFunction.hpp"
#include "Tetris.hpp"
#include "Timer.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_scancode.h>
#include <array>
#include <chrono>

class KeyboardListener {
public:
  enum class AppResult { Continue, Quit };

  KeyboardListener(Tetris &t) : tetris(t) {}

  [[nodiscard]] auto process_input(std::chrono::nanoseconds delta) -> AppResult;

private:
  Tetris &tetris;

  struct RepeatableAction {
    SDL_Scancode scancode;
    Timer input_delay;
    PeriodicFunction periodic_func;
  };

  std::array<RepeatableAction, 3> repeatable_actions = {{
      {.scancode = SDL_SCANCODE_A,
       .input_delay{std::chrono::milliseconds(100)},
       .periodic_func{std::chrono::milliseconds(60),
                      [this] { tetris.player_step_left(); }}},

      {.scancode = SDL_SCANCODE_S,
       .input_delay{std::chrono::milliseconds(100)},
       .periodic_func{std::chrono::milliseconds(60),
                      [this] { tetris.player_soft_drop(); }}},

      {.scancode = SDL_SCANCODE_D,
       .input_delay{std::chrono::milliseconds(100)},
       .periodic_func{std::chrono::milliseconds(60),
                      [this] { tetris.player_step_right(); }}},
  }};

  bool prev_keyboard[SDL_SCANCODE_COUNT]{};
};
