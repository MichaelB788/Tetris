#ifndef TETRIS_APP_HPP
#define TETRIS_APP_HPP
#include "Clock.hpp"
#include "EventHandler.hpp"
#include "IRenderer.hpp"
#include "IWindow.hpp"
#include "Tetris.hpp"
#include "TetrisRenderer.hpp"
#include <filesystem>
#include <thread>

class TetrisApp {
public:
  struct Specification {
    std::unique_ptr<IWindow> window;
    std::unique_ptr<IRenderer> renderer;
    std::optional<std::filesystem::path> controls;
    std::chrono::milliseconds gravity_rate;
  };

  explicit TetrisApp(Specification spec);

  void run();

private:
  void process_input() { event_handler_.handle_event(tetris_, *window_); }

  void sleep(std::chrono::milliseconds ms) { std::this_thread::sleep_for(ms); }

  void render_frame();

  void update_layout();

  void update_state();

  void handle_tetris_state();

  void update_gravity();

  void reset();

  std::unique_ptr<IWindow> window_;

  std::unique_ptr<IRenderer> renderer_;

  TetrisRenderer tetris_renderer_;

  EventHandler event_handler_;

  Tetris tetris_;

  Clock gravity_clock_;
};

#endif
