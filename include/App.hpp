#pragma once
#include "KeyboardListener.hpp"
#include "Tetris.hpp"
#include "TetrisRenderer.hpp"
#include <SDL3/SDL_init.h>
#include <chrono>
#include <filesystem>
#include <random>

class App {
public:
  App(const std::filesystem::path &atlas_path,
      const std::filesystem::path &font_path)
      : tetris_renderer(atlas_path, font_path) {}

  void loop();

private:
  std::mt19937 rng{std::random_device{}()};

  std::chrono::time_point<std::chrono::steady_clock> prev_time{
      std::chrono::steady_clock::now()};
  std::chrono::time_point<std::chrono::steady_clock> curr_time{
      std::chrono::steady_clock::now()};

  SDL_Event event{};
  Tetris tetris{rng};
  KeyboardListener keyboard_listener{tetris};
  TetrisRenderer tetris_renderer;
};
