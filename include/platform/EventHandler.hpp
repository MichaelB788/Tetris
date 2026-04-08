#pragma once
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <array>
#include <filesystem>

class TetrisGame;
using Command = void (TetrisGame::*)();

class EventHandler {
public:
  explicit EventHandler(TetrisGame &game,
                        const std::filesystem::path &config_path);

  void handle_kb_input();

private:
  void parse_controls(std::istream &input);

  TetrisGame &tetris_;

  std::array<std::pair<SDL_Scancode, Command>, 7> controls_;
};
