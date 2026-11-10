#pragma once
#include "Tetris.hpp"
#include "Timer.hpp"
#include <SDL3/SDL_scancode.h>
#include <array>
#include <chrono>

class KeyboardListener {
public:
  enum class AppResult { Continue, Quit };

  [[nodiscard]] auto process_keystrokes(Tetris &tetris,
                                        std::chrono::nanoseconds delta)
      -> AppResult;

private:
  struct RepeatableAction {
    SDL_Scancode scancode{};
    Timer input_delay{}, repeat_delay{};
    void (Tetris::*handler)(){};
  };

  std::array<RepeatableAction, 3> repeatable_actions = {{
      {SDL_SCANCODE_A,
       {std::chrono::milliseconds(110)},
       {std::chrono::milliseconds(50)},
       &Tetris::player_step_left},
      {SDL_SCANCODE_S,
       {std::chrono::milliseconds(110)},
       {std::chrono::milliseconds(50)},
       &Tetris::player_soft_drop},
      {SDL_SCANCODE_D,
       {std::chrono::milliseconds(110)},
       {std::chrono::milliseconds(50)},
       &Tetris::player_step_right},
  }};

  bool prev_keyboard[SDL_SCANCODE_COUNT]{};
};
