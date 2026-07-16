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
      : renderer_(atlas_path, font_path) {}

  void update_frame();
  void handle_window_resize_event();

private:
  void tick(std::chrono::nanoseconds delta);
  void handle_tetris_state();

  std::mt19937 rng_{std::random_device{}()};

  std::chrono::time_point<std::chrono::steady_clock>
      prev_time_ = std::chrono::steady_clock::now(),
      curr_time_ = std::chrono::steady_clock::now();

  FPS fps_{60};

  Tetris tetris_{rng_};
  EventHandler handler_;
  AppRenderer renderer_;
};
