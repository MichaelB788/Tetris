#pragma once
#include "core/TetrisGame.hpp"
#include "platform/EventHandler.hpp"
#include "platform/PlatformSDL.hpp"
#include "render/TetrisGameRenderer.hpp"
#include "render/TextRenderer.hpp"
#include <SDL3/SDL_render.h>
#include <filesystem>
#include <random>
#include <utility>

class TetrisApp {
public:
  struct Specification {
    std::filesystem::path controls;
    std::filesystem::path tetromino_atlas;
    std::filesystem::path font_path;
    float font_size;
    int target_fps;
  };

  explicit TetrisApp(const Specification &spec);

  void run();

private:
  void poll_events();

  void render_frame();

  void center_within_window();

  void handle_tetris_state();

  void reset() { tetris_ = TetrisGame{rng_}; }

  bool running_ = true;

  int target_fps_ = 60;

  std::pair<int, int> win_size_{800, 1000};

  Window window_{SDL_CreateWindow("Tetris", win_size_.first, win_size_.second,
                                  SDL_WINDOW_RESIZABLE)};

  Renderer renderer_{SDL_CreateRenderer(window_.get(), nullptr)};

  std::mt19937 rng_{std::random_device{}()};

  TetrisGame tetris_{rng_};

  TetrisGameRenderer tetris_renderer_;

  TextRenderer text_renderer_;

  EventHandler handler_;
};
