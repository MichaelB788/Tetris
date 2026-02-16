#ifndef TETRIS_EVENT_HANDLER_HPP
#define TETRIS_EVENT_HANDLER_HPP
#include <SDL3/SDL_events.h>
#include <array>
#include <filesystem>
#include <optional>

class Tetris;
class Rect;

class EventHandler {
public:
  using Command = void (Tetris::*)();

  explicit EventHandler(std::optional<std::filesystem::path> config);

  void handle_event(Tetris &tetris, SDL_Window *window, int &w, int &h);

  [[nodiscard]] bool should_quit() const { return should_quit_; }

private:
  void parse_controls_config(const std::filesystem::path &path_to_conf);

  SDL_Event sdl_event_;

  bool should_quit_ = false;

  std::array<std::pair<SDL_Keycode, Command>, 7> controls_;
};

#endif
