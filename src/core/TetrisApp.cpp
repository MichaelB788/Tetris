#include "core/TetrisApp.hpp"
#include "SDL3/SDL_render.h"
#include "platform/PlatformSDL.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_surface.h>

TetrisApp::TetrisApp(Specification spec)
    : piece_atlas_(
          sdl::img::create_texture_from_img(*renderer_, spec.tetromino_atlas)),
      handler_(tetris_, spec.controls) {
  auto ghost_surf = sdl::img::create_surface_from_img(spec.tetromino_atlas);
  SDL_SetSurfaceAlphaMod(ghost_surf.get(), 0x80);
  ghost_atlas_ = sdl::create_texture_from_surface(*renderer_, *ghost_surf);
}

void TetrisApp::run() {
  while (running_) {
    handle_events();
    update_state();
    center_layout();
    render_frame();
    sleep(std::chrono::milliseconds(12));
  }
}

void TetrisApp::handle_events() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_EVENT_QUIT:
      running_ = false;
      break;
    case SDL_EVENT_WINDOW_RESIZED: {
      auto &[w, h] = win_size_;
      SDL_GetWindowSizeInPixels(window_.get(), &w, &h);
    } break;
    case SDL_EVENT_KEY_DOWN:
      handler_.handle_kb_input(e);
      break;
    default:
      break;
    }
  }
}

void TetrisApp::render_frame() {
  static const auto [r, g, b, a] = SDL_Color(0x17, 0x18, 0x28, 0xFF);
  SDL_SetRenderDrawColor(renderer_.get(), r, g, b, a);
  SDL_RenderClear(renderer_.get());

  tetris_renderer_.draw_frame(tetris_, *renderer_, *piece_atlas_,
                              *ghost_atlas_);

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

  update_level();
}

void TetrisApp::update_level() {
  using namespace std::chrono_literals;
  static constexpr std::array<std::pair<unsigned, std::chrono::milliseconds>,
                              10>
      levels{{
          {10, 1000ms},
          {20, 900ms},
          {30, 800ms},
          {40, 700ms},
          {50, 600ms},
          {60, 500ms},
          {70, 450ms},
          {80, 400ms},
          {90, 300ms},
          {100, 200ms},
      }};

  unsigned score = tetris_.score();

  auto it = std::ranges::find_if(
      levels, [score](const auto &entry) { return score < entry.first; });

  if (it != std::end(levels))
    gravity_clock_.activate_in(it->second);
  else
    gravity_clock_.activate_in(100ms);
}

void TetrisApp::handle_tetris_state() {
  if (tetris_.status() == Status::GameOver)
    tetris_ = {};
}

void TetrisApp::center_layout() {
  tetris_renderer_.align_inside_rect(win_size_);

  // text_renderer_.adjust_lhs(hud_renderer_.queue_offset());
  // text_renderer_.adjust_rhs(hud_renderer_.hold_offset());
}

void TetrisApp::reset() {
  tetris_ = {};
  gravity_clock_ = Clock(std::chrono::milliseconds(1000));
}
