#pragma once
#include "core/TetrisGame.hpp"
#include "platform/EventHandler.hpp"
#include "platform/PlatformSDL.hpp"
#include "render/TetrisGameRenderer.hpp"
#include "render/TextRenderer.hpp"
#include <filesystem>
#include <utility>

class TetrisApp {
public:
  struct Specification {
    std::filesystem::path controls;
    std::filesystem::path tetromino_atlas;
    std::filesystem::path font_path;
    float font_size;
  };

  explicit TetrisApp(const Specification &spec)
      : tetris_renderer_(spec.tetromino_atlas, renderer_.get()),
        text_renderer_(spec.font_path, spec.font_size, renderer_.get()),
        handler_(tetris_, spec.controls) {}

  void run();

private:
  void handle_events();

  void render_frame();

  void center_within_window();

  void handle_tetris_state();

  void reset() { tetris_ = {}; }

  bool running_ = true;

  std::pair<int, int> win_size_{800, 800};

  sdl::Window window_ = sdl::create_window(
      "Tetris", win_size_.first, win_size_.second, SDL_WINDOW_RESIZABLE);

  sdl::Renderer renderer_ = sdl::create_renderer(window_.get());

  TetrisGame tetris_{};

  TetrisGameRenderer tetris_renderer_;

  TextRenderer text_renderer_;

  EventHandler handler_;
};
