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
      : app_renderer_(atlas_path, font_path) {}

  void listen_to_keyboard_input();
  void tick();
  void handle_tetris_state();
  void render_frame();
  void sleep_thread() const;

  void handle_window_resize_event();

private:
  std::mt19937 rng_{std::random_device{}()};

  std::chrono::time_point<std::chrono::steady_clock>
      prev_time_ = std::chrono::steady_clock::now(),
      curr_time_ = std::chrono::steady_clock::now();

  FPS fps_{60};
  FPS_Counter fps_counter_{};

  Tetris tetris_{rng_};
  EventHandler handler_;
  AppRenderer app_renderer_;
};
