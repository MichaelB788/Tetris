#pragma once
#include "Tetris.hpp"
#include "Timer.hpp"
#include <SDL3/SDL_scancode.h>
#include <array>

class EventHandler {
public:
  enum class KeyPress { FirstPress, HeldDown, None };

  void handle_kb_input(Tetris &tetris, std::mt19937 &rng,
                       std::chrono::nanoseconds delta);

private:
  void handle_first_key_press(Tetris &tetris, Tetris::Command command,
                              std::mt19937 &rng);

  void handle_key_down(Tetris &tetris, Tetris::Command action,
                       std::mt19937 &rng, std::chrono::nanoseconds delta);

  struct InputTiming {
    Timer init_delay;
    Timer repeat_interval;
  };

  InputTiming rotation_{.init_delay{std::chrono::milliseconds(300)},
                        .repeat_interval{std::chrono::milliseconds(100)}};

  InputTiming movement_{.init_delay{std::chrono::milliseconds(200)},
                        .repeat_interval{std::chrono::milliseconds(30)}};

  std::array<std::pair<SDL_Scancode, Tetris::Command>, 8> controls_{
      {{SDL_SCANCODE_W, Tetris::Command::HardDrop},
       {SDL_SCANCODE_A, Tetris::Command::MoveLeft},
       {SDL_SCANCODE_S, Tetris::Command::SoftDrop},
       {SDL_SCANCODE_D, Tetris::Command::MoveRight},
       {SDL_SCANCODE_UP, Tetris::Command::Hold},
       {SDL_SCANCODE_RIGHT, Tetris::Command::RotateClockwise},
       {SDL_SCANCODE_LEFT, Tetris::Command::RotateCounterclockwise},
       {SDL_SCANCODE_DOWN, Tetris::Command::RotateHalf}}};

  bool prev_kb_state_[SDL_SCANCODE_COUNT]{};
};
