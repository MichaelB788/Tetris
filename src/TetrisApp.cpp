#include "TetrisApp.hpp"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"

TetrisApp::TetrisApp(Specification spec)
    : window_{spec.platform.create_window("Tetris", win_w, win_h,
                                          SDL_WINDOW_RESIZABLE)},
      renderer_{spec.platform.create_renderer(window_)},
      event_handler_(spec.controls), gravity_clock_(spec.gravity_rate) {
  PlatformSDL::Surface surf =
      spec.platform.create_surface_from_img("assets/sprites/tetromino.png");
  textures_[NORM_ATLAS] =
      spec.platform.create_texture_from_surface(renderer_, surf);

  SDL_SetSurfaceAlphaMod(surf.get(), 100);

  textures_[GHOST_ATLAS] =
      spec.platform.create_texture_from_surface(renderer_, surf);

  board_renderer_ = {renderer_.get(), textures_[NORM_ATLAS].get(),
                     textures_[GHOST_ATLAS].get()};
  hud_renderer_ = {renderer_.get(), textures_[NORM_ATLAS].get()};
}

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
}

void TetrisApp::reset() {
  tetris_.reset();
  gravity_clock_.reset();
}
