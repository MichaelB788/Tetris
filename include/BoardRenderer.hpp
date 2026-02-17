#ifndef TETRIS_BOARD_RENDERER_HPP
#define TETRIS_BOARD_RENDERER_HPP
#include "PlatformSDL.hpp"
#include "Tetromino.hpp"

class Matrix;

class BoardRenderer {
public:
  BoardRenderer(const std::filesystem::path &path_to_atlas,
                SDL_Renderer &renderer);

  void draw_current(Tetromino::Projection current);

  void draw_ghost(Tetromino::Projection ghost);

  void draw_matrix(const Matrix &matrix);

  void center_within_window(int win_w, int win_h);

  [[nodiscard]] Point pos() const { return offset_; }

private:
  void draw_matrix_outline();

private:
  SDL_Renderer &renderer_;

  PlatformSDL::Texture atlas_{};

  PlatformSDL::Texture ghost_atlas_{};

  Point offset_{0, 0};
};
#endif
