#pragma once
#include "AppRenderer.hpp"
#include "EventHandler.hpp"
#include "FPS.hpp"
#include "Tetris.hpp"
#include <chrono>
#include <filesystem>
#include <random>

class AppState {
public:
  AppState(const std::filesystem::path &atlas_path,
           const std::filesystem::path &font_path)
      : renderer(atlas_path, font_path), handler(tetris) {}

  void update_frame();
  void handle_window_resize_event();

private:
  void tick(std::chrono::nanoseconds delta);
  void handle_tetris_state();

  std::mt19937 rng{std::random_device{}()};
  std::chrono::time_point<std::chrono::steady_clock>
      prev_time = std::chrono::steady_clock::now(),
      curr_time = std::chrono::steady_clock::now();

  FPS fps{60};
  Tetris tetris{rng};
  EventHandler handler;
  AppRenderer renderer;
};
