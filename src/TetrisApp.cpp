#include "TetrisApp.hpp"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"

TetrisApp::TetrisApp(Specification spec)
    : window_{spec.platform.create_window("Tetris", 600, 600,
                                          SDL_WINDOW_RESIZABLE)},
      renderer_{spec.platform.create_renderer(window_)},
      norm_atlas_{nullptr, &SDL_DestroyTexture},
      ghost_atlas_{nullptr, &SDL_DestroyTexture}, event_handler_(spec.controls),
      gravity_clock_(spec.gravity_rate) {
  PlatformSDL::Surface surf =
      spec.platform.create_surface_from_img("assets/sprites/tetromino.png");
  norm_atlas_ = spec.platform.create_texture_from_surface(renderer_, surf);

  SDL_SetSurfaceAlphaMod(surf.get(), 100);

  ghost_atlas_ = spec.platform.create_texture_from_surface(renderer_, surf);

  br_ = {renderer_.get(), norm_atlas_.get(), ghost_atlas_.get()};
  hr_ = {renderer_.get(), norm_atlas_.get()};
}

void TetrisApp::run() {
  while (!event_handler_.should_quit()) {
    event_handler_.handle_event(tetris_);
    update_state();
    update_layout();
    render_frame();
    sleep(std::chrono::milliseconds(12));
  }
}

void TetrisApp::render_frame() {
  static constexpr SDL_Color dark{.r = 0x27, .g = 0x2C, .b = 0x34, .a = 0xFF};

  SDL_SetRenderDrawColor(renderer_.get(), dark.r, dark.g, dark.b, dark.a);
  SDL_RenderClear(renderer_.get());

  br_.draw_ghost(tetris_.ghost());
  br_.draw_current(tetris_.current());
  br_.draw_matrix(tetris_.matrix());

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

void TetrisApp::update_layout() {}

void TetrisApp::reset() {
  tetris_.reset();
  gravity_clock_.reset();
}
