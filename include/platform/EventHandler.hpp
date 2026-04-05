#pragma once
#include <SDL3/SDL_events.h>
#include <array>
#include <filesystem>

class TetrisGame;
using Command = void (TetrisGame::*)();

class EventHandler {
public:
  explicit EventHandler(TetrisGame &game,
                        const std::filesystem::path &config_path);

  void handle_kb_input(SDL_Event &event);

private:
  void parse_controls(std::istream &input);

  TetrisGame &tetris_;

  std::array<std::pair<SDL_Keycode, Command>, 7> controls_;
};
