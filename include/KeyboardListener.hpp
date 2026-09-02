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

  struct Action {
    SDL_Scancode scancode;
    Timer input_delay;
    PeriodicFunction func;
  };

  std::array<Action, 7> actions = {{
      {.scancode = SDL_SCANCODE_W,
       .input_delay{std::chrono::milliseconds(100)},
       .func{std::chrono::milliseconds(60), [this] { tetris.hard_drop(); }}},
      {.scancode = SDL_SCANCODE_A,
       .input_delay{std::chrono::milliseconds(100)},
       .func{std::chrono::milliseconds(60), [this] { tetris.move_left(); }}},
      {.scancode = SDL_SCANCODE_S,
       .input_delay{std::chrono::milliseconds(100)},
       .func{std::chrono::milliseconds(60), [this] { tetris.soft_drop(); }}},
      {.scancode = SDL_SCANCODE_D,
       .input_delay{std::chrono::milliseconds(100)},
       .func{std::chrono::milliseconds(60), [this] { tetris.move_right(); }}},
      {.scancode = SDL_SCANCODE_LEFT,
       .input_delay{std::chrono::milliseconds(100)},
       .func{std::chrono::milliseconds(100), [this] { tetris.rotate_ccw(); }}},
      {.scancode = SDL_SCANCODE_RIGHT,
       .input_delay{std::chrono::milliseconds(100)},
       .func{std::chrono::milliseconds(100), [this] { tetris.rotate_cw(); }}},
      {.scancode = SDL_SCANCODE_DOWN,
       .input_delay{std::chrono::milliseconds(100)},
       .func{std::chrono::milliseconds(100), [this] { tetris.rotate_half(); }}},
  }};

  bool prev_keyboard[SDL_SCANCODE_COUNT]{};
};
