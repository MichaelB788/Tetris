#pragma once
#include "EventHandler.hpp"
#include "FPS.hpp"
#include "NumberRenderer.hpp"
#include "PlatformSDL.hpp"
#include "ScreenPos.hpp"
#include "Tetris.hpp"
#include "TextRenderer.hpp"
#include <chrono>
#include <filesystem>
#include <random>

class AppState {
public:
  struct Configuration {
    std::filesystem::path atlas_path;
    std::filesystem::path font_path;
    std::filesystem::path custom_controls_path;
  };

  AppState(const Configuration &config);

  void listen_to_keyboard_input();
  void tick();
  void handle_tetris_state();
  void render_frame();
  void sleep_thread() const;

  void handle_window_resize_event();

private:
  void render_game_objects() const;
  void render_screen_text();
  void render_screen_numbers() const;

  std::mt19937 rng_{std::random_device{}()};

  std::chrono::time_point<std::chrono::steady_clock>
      prev_time_ = std::chrono::steady_clock::now(),
      curr_time_ = std::chrono::steady_clock::now();

  FPS fps_{60};
  FPS_Counter fps_counter_{};

  screen_pos::Playfield pf_pos_;
  screen_pos::Text text_pos_;

  Tetris tetris_{rng_};

  EventHandler handler_;

  TextRenderer text_renderer_{};
  NumberRenderer num_renderer_{nullptr, nullptr};

  SDL::Window window_ = nullptr;
  SDL::Renderer renderer_ = nullptr;
  SDL::Texture texture_atlas_ = nullptr;
  SDL::TTF::RendererTextEngine text_engine_ = nullptr;
  SDL::TTF::Font font_ = nullptr;
};
