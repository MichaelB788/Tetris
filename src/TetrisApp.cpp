#include "TetrisApp.hpp"
#include "SDL3/SDL_render.h"

TetrisApp::TetrisApp(Specification spec)
    : window_(PlatformSDL::create_window("Tetris", win_w, win_h,
                                         SDL_WINDOW_RESIZABLE)),
      renderer_(PlatformSDL::create_renderer(window_.get())),
      text_renderer_(spec.font_path, spec.font_size, renderer_.get()),
      board_renderer_(spec.tetromino_atlas, renderer_.get()),
      hud_renderer_(spec.tetromino_atlas, renderer_.get()),
      event_handler_(spec.controls), gravity_clock_(spec.gravity_rate) {}

void TetrisApp::run() {
  while (!event_handler_.should_quit()) {
    process_input();
    update_state();
    center_layout();
    render_frame();
    sleep(std::chrono::milliseconds(12));
  }
}

void TetrisApp::render_frame() {
  static constexpr SDL_Color dark{.r = 0x17, .g = 0x18, .b = 0x2B, .a = 0xFF};

  SDL_SetRenderDrawColor(renderer_.get(), dark.r, dark.g, dark.b, dark.a);
  SDL_RenderClear(renderer_.get());

  board_renderer_.draw_ghost(tetris_.ghost());
  hud_renderer_.draw_held(tetris_.optional_hold());
  hud_renderer_.draw_next_queue(tetris_.next_queue());

  board_renderer_.draw_current(tetris_.current());
  board_renderer_.draw_matrix(tetris_.matrix());

  text_renderer_.render_text();
  text_renderer_.render_score(tetris_.score());

  SDL_RenderPresent(renderer_.get());
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

void TetrisApp::center_layout() {
  board_renderer_.center_within_window(win_w, win_h);
  hud_renderer_.wrap_around_board(board_renderer_.pos());
  text_renderer_.adjust_lhs(hud_renderer_.queue_offset());
  text_renderer_.adjust_rhs(hud_renderer_.hold_offset());
}

void TetrisApp::reset() {
  tetris_.reset();
  gravity_clock_.reset();
}
