#pragma once
#include "core/TetrisGame.hpp"
#include "platform/EventHandler.hpp"
#include "platform/PlatformSDL.hpp"
#include "render/BoardRenderer.hpp"
#include "render/HUDRenderer.hpp"
#include "render/TextRenderer.hpp"
#include "util/Clock.hpp"
#include <filesystem>
#include <thread>

class TetrisApp {
public:
  struct Specification {
    std::filesystem::path controls;
    std::filesystem::path tetromino_atlas;
    std::filesystem::path font_path;
    float font_size;
  };

  explicit TetrisApp(Specification spec)
      : text_renderer_(spec.font_path, spec.font_size, *renderer_),
        board_renderer_(spec.tetromino_atlas, *renderer_),
        hud_renderer_(spec.tetromino_atlas, *renderer_),
        event_handler_(spec.controls) {}

  void run();

private:
  void sleep(std::chrono::milliseconds ms) { std::this_thread::sleep_for(ms); }

  void process_input() {
    event_handler_.handle_event(tetris_, *window_, win_w, win_h);
  }

  void render_frame();

  void center_layout();

  void update_state();

  void update_level();

  void handle_tetris_state();

  void update_gravity();

  void reset();

private:
  int win_w = 600, win_h = 600;

  PlatformSDL::Window window_ =
      PlatformSDL::create_window("Tetris", win_w, win_h, SDL_WINDOW_RESIZABLE);

  PlatformSDL::Renderer renderer_ = PlatformSDL::create_renderer(*window_);

  TetrisGame tetris_{};

  Clock gravity_clock_ = Clock(std::chrono::milliseconds(1000));

  TextRenderer text_renderer_;

  BoardRenderer board_renderer_;

  HUDRenderer hud_renderer_;

  EventHandler event_handler_;
};
