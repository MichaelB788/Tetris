#ifndef TETRIS_APP_HPP
#define TETRIS_APP_HPP
#include "BoardRenderer.hpp"
#include "Clock.hpp"
#include "EventHandler.hpp"
#include "HUDRenderer.hpp"
#include "PlatformSDL.hpp"
#include "Tetris.hpp"
#include <filesystem>
#include <optional>
#include <thread>

class TetrisApp {
public:
  struct Specification {
    const PlatformSDL &platform;
    const std::optional<std::filesystem::path> &controls;
    std::chrono::milliseconds gravity_rate;
  };

  explicit TetrisApp(Specification spec);

  void run();

private:
  void sleep(std::chrono::milliseconds ms) { std::this_thread::sleep_for(ms); }

  void process_input() {
    event_handler_.handle_event(tetris_, window_.get(), win_w, win_h);
  }

  void render_frame();

  void center_layout();

  void update_state();

  void handle_tetris_state();

  void update_gravity();

  void reset();

private:
  int win_w = 600, win_h = 600;

  PlatformSDL::Window window_;

  PlatformSDL::Renderer renderer_;

  enum Textures { NORM_ATLAS, GHOST_ATLAS, COUNT };
  std::array<PlatformSDL::Texture, COUNT> textures_{};

  EventHandler event_handler_;

  Tetris tetris_;

  BoardRenderer board_renderer_{nullptr, nullptr, nullptr};

  HUDRenderer hud_renderer_{nullptr, nullptr};

  Clock gravity_clock_;
};

#endif
