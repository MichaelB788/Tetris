#ifndef TETRIS_BOARD_RENDERER_HPP
#define TETRIS_BOARD_RENDERER_HPP
#include "Tetromino.hpp"

class SDL_Renderer;
class SDL_Texture;
class Matrix;

class BoardRenderer {
public:
  BoardRenderer(SDL_Renderer *renderer, SDL_Texture *norm_atlas,
                SDL_Texture *ghost_atlas)
      : renderer_(renderer), norm_atlas_(norm_atlas),
        ghost_atlas_(ghost_atlas) {}

  void draw_current(Tetromino::Projection current);

  void draw_ghost(Tetromino::Projection ghost);

  void draw_matrix(const Matrix &matrix);

  void center_within_window(int win_w, int win_y);

  [[nodiscard]] Point get_offset() const { return offset_; }

private:
  void draw_matrix_outline();

private:
  SDL_Renderer *renderer_ = nullptr;

  SDL_Texture *norm_atlas_ = nullptr;

  SDL_Texture *ghost_atlas_ = nullptr;

  Point offset_{0, 0};
};
#endif
