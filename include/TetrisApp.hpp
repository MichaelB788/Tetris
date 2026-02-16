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

  void render_frame();

  void update_layout();

  void update_state();

  void handle_tetris_state();

  void update_gravity();

  void reset();

private:
  PlatformSDL::Window window_;

  PlatformSDL::Renderer renderer_;

  PlatformSDL::Texture norm_atlas_;

  PlatformSDL::Texture ghost_atlas_;

  EventHandler event_handler_;

  Tetris tetris_;

  BoardRenderer br_{nullptr, nullptr, nullptr};

  HUDRenderer hr_{nullptr, nullptr};

  Clock gravity_clock_;
};

#endif
