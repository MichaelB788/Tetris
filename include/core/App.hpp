#pragma once
#include "core/Tetris.hpp"
#include "platform/EventHandler.hpp"
#include "platform/PlatformSDL.hpp"
#include "render/GameRenderer.hpp"
#include "render/TextRenderer.hpp"
#include <SDL3/SDL_render.h>
#include <chrono>
#include <filesystem>
#include <random>

class TetrisApp {
public:
  struct Specification {
    std::filesystem::path controls;
    std::filesystem::path tetromino_atlas;
    std::filesystem::path font_path;
    int target_fps = 60;
  };

  explicit TetrisApp(const Specification &spec);

  void run();

private:
  void render_frame();

  void handle_tetris_state();

  bool running_ = true;
  int target_fps_{};

  std::chrono::time_point<std::chrono::steady_clock> prev_time{
      std::chrono::steady_clock::now()};
  std::chrono::time_point<std::chrono::steady_clock> curr_time{};
  std::mt19937 rng_{std::random_device{}()};

  SDL::Window window_{
      SDL_CreateWindow("Tetris", 800, 800, SDL_WINDOW_RESIZABLE)};
  SDL::Renderer renderer_{SDL_CreateRenderer(window_.get(), nullptr)};

  Tetris tetris_{rng_};
  GameRenderer tetris_renderer_;
  TextRenderer text_renderer_;
  EventHandler handler_;
};
