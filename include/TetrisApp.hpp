#ifndef TETRIS_APP_HPP
#define TETRIS_APP_HPP
#include "BoardRenderer.hpp"
#include "Clock.hpp"
#include "EventHandler.hpp"
#include "HUDRenderer.hpp"
#include "PlatformSDL.hpp"
#include "Tetris.hpp"
#include "TextRenderer.hpp"
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

  explicit TetrisApp(Specification spec);

  void run();

private:
  void sleep(std::chrono::milliseconds ms) { std::this_thread::sleep_for(ms); }

  void process_input() {
    event_handler_.handle_event(tetris_, window_.get(), win_w, win_h);
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

  PlatformSDL::Window window_;

  PlatformSDL::Renderer renderer_;

  TextRenderer text_renderer_;

  BoardRenderer board_renderer_;

  HUDRenderer hud_renderer_;

  Tetris tetris_;

  EventHandler event_handler_;

  Clock gravity_clock_;
};

#endif
