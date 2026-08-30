#pragma once
#include "AppRenderer.hpp"
#include "EventHandler.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_init.h>
#include <chrono>
#include <filesystem>
#include <random>

class App {
public:
  App(const std::filesystem::path &atlas_path,
      const std::filesystem::path &font_path)
      : renderer(atlas_path, font_path) {}

  void loop();

private:
  std::mt19937 rng{std::random_device{}()};

  std::chrono::time_point<std::chrono::steady_clock>
      previous_frame_start = std::chrono::steady_clock::now(),
      current_frame_start = std::chrono::steady_clock::now();

  Tetris tetris{rng};
  EventHandler handler{};
  AppRenderer renderer;
};
