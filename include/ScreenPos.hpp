#pragma once
#include "Point.hpp"

struct SDL_Window;

namespace ScreenPos {
struct Playfield {
  Point<float> board{};
  Point<float> queue{};
  Point<float> hold{};
};

struct Text {
  Point<float> next{};
  Point<float> hold{};
  Point<float> score_label{};
  Point<float> score_val{};
  Point<float> fps_label{};
  Point<float> fps_val{};
};

void fit_offsets_within_window(ScreenPos::Playfield &pf_pos,
                               ScreenPos::Text &text_pos, SDL_Window &win);
} // namespace ScreenPos
