#pragma once
#include "PeriodicFunction.hpp"
#include "Tetris.hpp"
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
    PeriodicFunction func;
  };

  std::array<Action, 7> actions = {{
      {.scancode = SDL_SCANCODE_W,
       .func{std::chrono::milliseconds(120), [this] { tetris.hard_drop(); }}},
      {.scancode = SDL_SCANCODE_A,
       .func{std::chrono::milliseconds(120), [this] { tetris.move_left(); }}},
      {.scancode = SDL_SCANCODE_S,
       .func{std::chrono::milliseconds(120), [this] { tetris.soft_drop(); }}},
      {.scancode = SDL_SCANCODE_D,
       .func{std::chrono::milliseconds(120), [this] { tetris.move_right(); }}},
      {.scancode = SDL_SCANCODE_LEFT,
       .func{std::chrono::milliseconds(120), [this] { tetris.rotate_ccw(); }}},
      {.scancode = SDL_SCANCODE_RIGHT,
       .func{std::chrono::milliseconds(120), [this] { tetris.rotate_cw(); }}},
      {.scancode = SDL_SCANCODE_DOWN,
       .func{std::chrono::milliseconds(120), [this] { tetris.rotate_half(); }}},
  }};

  bool prev_keyboard[SDL_SCANCODE_COUNT]{};
};
