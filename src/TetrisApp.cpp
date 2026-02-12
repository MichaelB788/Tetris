#include "TetrisApp.hpp"

TetrisApp::TetrisApp(Specification spec)
    : window_(std::move(spec.window)), renderer_(std::move(spec.renderer)),
      tetris_renderer_(*renderer_), event_handler_(std::move(spec.controls)),
      gravity_clock_(spec.gravity_rate) {}

void TetrisApp::run() {
  while (!event_handler_.should_quit()) {
    process_input();
    update_state();
    update_layout();
    render_frame();
    sleep(std::chrono::milliseconds(12));
  }
}

void TetrisApp::render_frame() {
  renderer_->set_color({.r = 39, .g = 44, .b = 52, .a = 255});
  renderer_->clear();

  tetris_renderer_.draw_frame(tetris_);

  renderer_->present();
}

void TetrisApp::update_state() {
  update_gravity();
  handle_tetris_state();
}

void TetrisApp::update_gravity() {
  gravity_clock_.tick();

  if (gravity_clock_.has_set_off()) {
    tetris_.move_down();
    gravity_clock_.reset();
  }
}

void TetrisApp::handle_tetris_state() {
  switch (tetris_.state()) {
  case Tetris::State::GameOver:
    reset();
    break;
  case Tetris::State::Paused:
    break;
  case Tetris::State::Running:
    break;
  }
}

void TetrisApp::update_layout() {
  auto [w, h] = window_->get_window_size();
  tetris_renderer_.adjust_offset(w, h);
}

void TetrisApp::reset() {
  tetris_.reset();
  gravity_clock_.reset();
}
