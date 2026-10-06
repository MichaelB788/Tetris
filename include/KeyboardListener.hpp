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
      {SDL_SCANCODE_A,
       {std::chrono::milliseconds(100)},
       {std::chrono::milliseconds(60), [this] { tetris.player_step_left(); }}},

      {SDL_SCANCODE_S,
       {std::chrono::milliseconds(100)},
       {std::chrono::milliseconds(60), [this] { tetris.player_soft_drop(); }}},

      {SDL_SCANCODE_D,
       {std::chrono::milliseconds(100)},
       {std::chrono::milliseconds(60), [this] { tetris.player_step_right(); }}},
  }};

  bool prev_keyboard[SDL_SCANCODE_COUNT]{};
};
