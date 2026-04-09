#pragma once
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
  bool first_key_press = true;

  explicit EventHandler(TetrisGame &game,
                        const std::filesystem::path &config_path);

  void handle_kb_input(std::chrono::nanoseconds delta);

private:
  Timer rapid_fire_delay_{.duration = std::chrono::milliseconds(300)};

  std::array<bool, SDL_SCANCODE_COUNT> prev_kb_state_{};

  void parse_controls(std::istream &input);

  TetrisGame &tetris_;

  std::array<std::pair<SDL_Scancode, Command>, 7> controls_;
};
