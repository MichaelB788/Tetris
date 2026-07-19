#pragma once
#include "Timer.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_scancode.h>
#include <chrono>
#include <optional>

class Tetris;

class EventHandler {
public:
  void handle_game_events(Tetris &tetris, const bool *curr_keyboard);
  void handle_paused_events(Tetris &tetris, const bool *curr_keyboard);
  [[nodiscard]] auto handle_game_over_events(Tetris &tetris,
                                             const bool *curr_keyboard)
      -> SDL_AppResult;

  void tick(Tetris &tetris, std::chrono::nanoseconds delta);

private:
  enum Event : uint16_t {
    NULL_CMD = 0x0,
    MOVE_LEFT_CMD = 0x1,
    MOVE_RIGHT_CMD = 0x2,
    SOFT_DROP_CMD = 0x4,
    HARD_DROP_CMD = 0x8,
    ROTATE_CW_CMD = 0x10,
    ROTATE_CCW_CMD = 0x20,
    ROTATE_HALF_CMD = 0x40,
    HOLD_ACTIVE_CMD = 0x80,
    TOGGLE_PAUSE_CMD = 0x100
  };

  struct InputTimer {
    Timer init_delay{};
    Timer repeat_interval{};
  };

  struct Command {
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;
    Event event = NULL_CMD;
    std::optional<InputTimer> timer = std::nullopt;
  };

  void execute_command(Tetris &tetris, Command &command);

  static constexpr InputTimer MOVEMENT_TIMER{
      .init_delay{std::chrono::milliseconds(150)},
      .repeat_interval{std::chrono::milliseconds(50)}};
  static constexpr InputTimer ROTATION_TIMER{
      .init_delay{std::chrono::milliseconds(300)},
      .repeat_interval{std::chrono::milliseconds(100)}};

  uint16_t pending_held_events = 0;

  std::array<Command, 9> controls{
      {{.scancode = SDL_SCANCODE_W,
        .event = HARD_DROP_CMD,
        .timer = MOVEMENT_TIMER},

       {.scancode = SDL_SCANCODE_S,
        .event = SOFT_DROP_CMD,
        .timer = MOVEMENT_TIMER},

       {.scancode = SDL_SCANCODE_D,
        .event = MOVE_RIGHT_CMD,
        .timer = MOVEMENT_TIMER},

       {.scancode = SDL_SCANCODE_A,
        .event = MOVE_LEFT_CMD,
        .timer = MOVEMENT_TIMER},

       {.scancode = SDL_SCANCODE_RIGHT,
        .event = ROTATE_CW_CMD,
        .timer = ROTATION_TIMER},

       {.scancode = SDL_SCANCODE_LEFT,
        .event = ROTATE_CCW_CMD,
        .timer = ROTATION_TIMER},

       {.scancode = SDL_SCANCODE_DOWN,
        .event = ROTATE_HALF_CMD,
        .timer = ROTATION_TIMER},

       {.scancode = SDL_SCANCODE_UP, .event = HOLD_ACTIVE_CMD},

       {.scancode = SDL_SCANCODE_SPACE, .event = TOGGLE_PAUSE_CMD}}};

  bool prev_keyboard[SDL_SCANCODE_COUNT]{};
};
