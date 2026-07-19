#pragma once
#include "AppRenderer.hpp"
#include "EventHandler.hpp"
#include "FPS.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_init.h>
#include <chrono>
#include <filesystem>
#include <random>

class AppState {
public:
  AppState(const std::filesystem::path &atlas_path,
           const std::filesystem::path &font_path)
      : renderer(atlas_path, font_path), handler() {}

  [[nodiscard]] auto update_frame() -> SDL_AppResult;

  void handle_window_resize_event();

private:
  [[nodiscard]] auto handle_keyboard_input() -> SDL_AppResult;

  void tick(std::chrono::nanoseconds delta);

  std::mt19937 rng{std::random_device{}()};
  std::chrono::time_point<std::chrono::steady_clock>
      prev_frame_start = std::chrono::steady_clock::now(),
      frame_start = std::chrono::steady_clock::now();

  FPS fps{60};
  Tetris tetris{rng};
  EventHandler handler{};
  AppRenderer renderer;
};
