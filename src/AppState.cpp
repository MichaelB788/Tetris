#include "AppState.hpp"
#include "PlatformSDL.hpp"
#include "Point.hpp"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include <chrono>
#include <thread>

void AppState::render_frame() {
  SDL_SetRenderDrawColor(renderer_.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(renderer_.get());

  game_renderer_.draw_snapshot(*renderer_, tetris.snapshot());

  // Render screen text
  {
    const auto hud_layout = game_renderer_.compute_hud_layout();
    text_renderer_.render_text("NEXT", hud_layout.next_label);
    text_renderer_.render_text("HOLD", hud_layout.hold_label);
    text_renderer_.render_text("SCORE", hud_layout.score_label);
    text_renderer_.render_int(tetris_.score(), hud_layout.score_value);
#ifndef NDEBUG
    text_renderer_.render_text("FPS", hud_layout.fps_label);
    text_renderer_.render_int(fps_counter_.fps, hud_layout.fps_value);
#endif
  }

  SDL_RenderPresent(renderer_.get());
}

void AppState::handle_tetris_state() {}
