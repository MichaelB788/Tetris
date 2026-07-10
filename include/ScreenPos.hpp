#pragma once
#include "Point.hpp"

struct SDL_Window;

namespace screen_pos {
struct Playfield {
  Point<float> board{};
  Point<float> seven_bag_pos{};
  Point<float> held_piece{};
};

struct Text {
  Point<float> next{};
  Point<float> hold{};
  Point<float> score_label{};
  Point<float> score_val{};
  Point<float> fps_label{};
  Point<float> fps_val{};
};

void fit_offsets_within_window(screen_pos::Playfield &pf_pos,
                               screen_pos::Text &text_pos, SDL_Window &win);
} // namespace screen_pos
