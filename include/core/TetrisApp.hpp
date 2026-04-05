#pragma once
#include "core/TetrisGame.hpp"
#include "platform/EventHandler.hpp"
#include "platform/PlatformSDL.hpp"
#include "render/TetrisGameRenderer.hpp"
#include "util/Clock.hpp"
#include <filesystem>
#include <thread>
#include <utility>

class TetrisApp {
public:
  struct Specification {
    std::filesystem::path controls;
    std::filesystem::path tetromino_atlas;
    std::filesystem::path font_path;
    float font_size;
  };

  explicit TetrisApp(Specification spec);

  void run();

private:
  void sleep(std::chrono::milliseconds ms) { std::this_thread::sleep_for(ms); }

  void handle_events();

  void render_frame();

  void center_layout();

  void update_state();

  void update_level();

  void handle_tetris_state();

  void update_gravity();

  void reset();

  bool running_ = true;

  std::pair<int, int> win_size_{800, 800};

  sdl::Window window_ = sdl::create_window(
      "Tetris", win_size_.first, win_size_.second, SDL_WINDOW_RESIZABLE);

  sdl::Renderer renderer_ = sdl::create_renderer(*window_);

  sdl::Texture piece_atlas_{nullptr, nullptr};

  sdl::Texture ghost_atlas_{nullptr, nullptr};

  TetrisGame tetris_{};

  TetrisGameRenderer tetris_renderer_{};

  Clock gravity_clock_ = Clock(std::chrono::milliseconds(1000));

  EventHandler handler_;
};
