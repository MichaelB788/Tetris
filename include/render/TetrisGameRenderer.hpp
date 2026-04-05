#pragma once
#include "util/Point.hpp"
#include <utility>

class TetrisGame;
class Board;
class HUD;
class SDL_Renderer;
class SDL_Texture;

class TetrisGameRenderer {
public:
  void draw_frame(const TetrisGame &game, SDL_Renderer &renderer,
                  SDL_Texture &piece_atlas, SDL_Texture &ghost_atlas);

  void align_inside_rect(std::pair<int, int> rect);

private:
  void draw_board(const Board &board, SDL_Renderer &renderer,
                  SDL_Texture &piece_atlas, SDL_Texture &ghost_atlas);

  void draw_hud(const HUD &hud, SDL_Renderer &renderer,
                SDL_Texture &piece_atlas);

  Point board_pos_{0, 0};

  Point queue_offset_{0, 0};

  Point hold_offset_{0, 0};
};
