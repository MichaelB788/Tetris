#pragma once
#include "Tetris.hpp"
#include "Timer.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <array>
#include <filesystem>

class EventHandler {
public:
  void handle_kb_input(Tetris &tetris, std::mt19937 &rng,
                       std::chrono::nanoseconds delta);

  auto set_controls_from_file(const std::filesystem::path &config_file) -> bool;

private:
  auto parse_config_file(std::istream &input) -> bool;

  void handle_first_key_press(Tetris &tetris, Tetris::Action command,
                              std::mt19937 &rng);

  void handle_key_down(Tetris &tetris, Tetris::Action action, std::mt19937 &rng,
                       std::chrono::nanoseconds delta);

  struct InputTiming {
    Timer init_delay;
    Timer repeat_interval;
  };

  InputTiming rotation_{.init_delay{std::chrono::milliseconds(300)},
                        .repeat_interval{std::chrono::milliseconds(100)}};

  InputTiming movement_{.init_delay{std::chrono::milliseconds(200)},
                        .repeat_interval{std::chrono::milliseconds(30)}};

  std::array<std::pair<SDL_Scancode, Tetris::Action>, 8> controls_{
      {{SDL_SCANCODE_W, Tetris::Action::HardDrop},
       {SDL_SCANCODE_A, Tetris::Action::MoveLeft},
       {SDL_SCANCODE_S, Tetris::Action::SoftDrop},
       {SDL_SCANCODE_D, Tetris::Action::MoveRight},
       {SDL_SCANCODE_UP, Tetris::Action::Hold},
       {SDL_SCANCODE_RIGHT, Tetris::Action::RotateClockwise},
       {SDL_SCANCODE_LEFT, Tetris::Action::RotateCounterclockwise},
       {SDL_SCANCODE_DOWN, Tetris::Action::RotateHalf}}};

  bool prev_kb_state_[SDL_SCANCODE_COUNT]{};
};
