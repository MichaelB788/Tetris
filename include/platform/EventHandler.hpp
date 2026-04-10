#pragma once
#include "core/TetrisGame.hpp"
#include "util/Timer.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <array>
#include <chrono>
#include <filesystem>

class TetrisGame;
using Command = void (TetrisGame::*)();

class EventHandler {
public:
  explicit EventHandler(TetrisGame &game,
                        const std::filesystem::path &config_path);

  void handle_kb_input(std::chrono::nanoseconds delta);

private:
  void parse_controls(std::istream &input);

  TetrisGame &tetris_;

  Timer delay_until_rapid_fire_{std::chrono::milliseconds(250)};

  Timer rapid_fire_delay_{std::chrono::microseconds(1000)};

  std::array<bool, SDL_SCANCODE_COUNT> prev_kb_state_{};

  std::array<std::pair<SDL_Scancode, Command>, 8> controls_{
      {{SDL_SCANCODE_W, &TetrisGame::hard_drop},
       {SDL_SCANCODE_A, &TetrisGame::move_left},
       {SDL_SCANCODE_S, &TetrisGame::soft_drop},
       {SDL_SCANCODE_D, &TetrisGame::move_right},
       {SDL_SCANCODE_UP, &TetrisGame::hold},
       {SDL_SCANCODE_RIGHT, &TetrisGame::rotate_cw},
       {SDL_SCANCODE_LEFT, &TetrisGame::rotate_ccw},
       {SDL_SCANCODE_DOWN, &TetrisGame::rotate_ht}}};
};
