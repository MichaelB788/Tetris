#pragma once
#include "core/TetrisGame.hpp"
#include "util/Timer.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <array>
#include <chrono>
#include <filesystem>

class EventHandler {
public:
  explicit EventHandler(TetrisGame &game,
                        const std::filesystem::path &config_path);

  void handle_kb_input(std::chrono::nanoseconds delta, std::mt19937 &rng);

private:
  struct InputTiming {
    Timer init_delay;
    Timer repeat_interval;
  };

  void parse_controls(std::istream &input);

  TetrisGame &tetris_;

  InputTiming rotation_{.init_delay{std::chrono::milliseconds(300)},
                        .repeat_interval{std::chrono::milliseconds(100)}};

  InputTiming movement_{.init_delay{std::chrono::milliseconds(200)},
                        .repeat_interval{std::chrono::milliseconds(30)}};

  std::array<bool, SDL_SCANCODE_COUNT> prev_kb_state_{};

  std::array<std::pair<SDL_Scancode, TetrisGame::Action>, 8> controls_{
      {{SDL_SCANCODE_W, TetrisGame::Action::HardDrop},
       {SDL_SCANCODE_A, TetrisGame::Action::MoveLeft},
       {SDL_SCANCODE_S, TetrisGame::Action::SoftDrop},
       {SDL_SCANCODE_D, TetrisGame::Action::MoveRight},
       {SDL_SCANCODE_UP, TetrisGame::Action::Hold},
       {SDL_SCANCODE_RIGHT, TetrisGame::Action::RotateClockwise},
       {SDL_SCANCODE_LEFT, TetrisGame::Action::RotateCounterclockwise},
       {SDL_SCANCODE_DOWN, TetrisGame::Action::RotateHalf}}};
};
