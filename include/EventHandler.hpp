#pragma once
#include "Tetris.hpp"
#include "Timer.hpp"
#include <SDL3/SDL_scancode.h>
#include <chrono>
#include <optional>
#include <random>

class EventHandler {
public:
  void listen_to_keyboard_input();

  void handle_new_events(Tetris &tetris, std::mt19937 &rng);
  void handle_repeated_events(Tetris &tetris, std::mt19937 &rng,
                              std::chrono::nanoseconds delta);

private:
  enum Command : uint16_t {
    // clang-format off
    NULL_CMD          = 0x0,
    MOVE_LEFT_CMD     = 0x1,
    MOVE_RIGHT_CMD    = 0x2,
    SOFT_DROP_CMD     = 0x4,
    HARD_DROP_CMD     = 0x8,
    ROTATE_CW_CMD     = 0x10,
    ROTATE_CCW_CMD    = 0x20,
    ROTATE_HALF_CMD   = 0x40,
    HOLD_ACTIVE_CMD   = 0x80,
    TOGGLE_PAUSE_CMD  = 0x100
    // clang-format on
  };

  auto idx_of_command(Command command) const -> int;
  void handle_command(Command command, Tetris &tetris, std::mt19937 &rng);

  struct InputTimer {
    Timer<std::chrono::nanoseconds> init_delay{};
    Timer<std::chrono::nanoseconds> repeat_interval{};
  };

  struct KeyboardCommand {
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;
    Command command = NULL_CMD;
    std::optional<InputTimer> timer = std::nullopt;
  };

  uint16_t pending_new_events = 0;
  uint16_t pending_held_events = 0;

  static constexpr InputTimer MOVEMENT_TIMER{
      .init_delay{std::chrono::milliseconds(150)},
      .repeat_interval{std::chrono::milliseconds(50)}};
  static constexpr InputTimer ROTATION_TIMER{
      .init_delay{std::chrono::milliseconds(300)},
      .repeat_interval{std::chrono::milliseconds(100)}};

  std::array<KeyboardCommand, 9> controls_{
      {{.scancode = SDL_SCANCODE_W,
        .command = HARD_DROP_CMD,
        .timer = MOVEMENT_TIMER},

       {.scancode = SDL_SCANCODE_S,
        .command = SOFT_DROP_CMD,
        .timer = MOVEMENT_TIMER},

       {.scancode = SDL_SCANCODE_D,
        .command = MOVE_RIGHT_CMD,
        .timer = MOVEMENT_TIMER},

       {.scancode = SDL_SCANCODE_A,
        .command = MOVE_LEFT_CMD,
        .timer = MOVEMENT_TIMER},

       {.scancode = SDL_SCANCODE_RIGHT,
        .command = ROTATE_CW_CMD,
        .timer = ROTATION_TIMER},

       {.scancode = SDL_SCANCODE_LEFT,
        .command = ROTATE_CCW_CMD,
        .timer = ROTATION_TIMER},

       {.scancode = SDL_SCANCODE_DOWN,
        .command = ROTATE_HALF_CMD,
        .timer = ROTATION_TIMER},

       {.scancode = SDL_SCANCODE_UP, .command = HOLD_ACTIVE_CMD},

       {.scancode = SDL_SCANCODE_SPACE, .command = TOGGLE_PAUSE_CMD}}};

  bool prev_keyboard[SDL_SCANCODE_COUNT]{};
};
