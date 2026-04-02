#pragma once
#include <SDL3/SDL_events.h>
#include <array>
#include <filesystem>

class Tetris;
class Rect;

class EventHandler {
public:
  using Command = void (Tetris::*)();

  explicit EventHandler(const std::filesystem::path &config_path);

  void handle_event(Tetris &tetris, SDL_Window &window, int &w, int &h);

  [[nodiscard]] bool should_quit() const { return should_quit_; }

private:
  void parse_controls(std::istream &input);

  SDL_Event sdl_event_;

  bool should_quit_ = false;

  std::array<std::pair<SDL_Keycode, Command>, 7> controls_;
};
