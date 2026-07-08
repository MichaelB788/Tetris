#pragma once
#include "PlatformSDL.hpp"
#include "Tetris.hpp"

namespace render::game {}

class GameRenderer {
public:
  void draw_snapshot(SDL_Renderer &renderer, const Tetris::Snapshot &game);

  void fit_within_window(SDL_Window &window);

private:
  enum class TetrominoRenderType { Ghost, Normal };
  void draw_tetromino_tile(SDL_Renderer &renderer, Tetromino::Type type,
                           TetrominoRenderType render_type,
                           Point<int> tetromino_pos, Point<float> offset);

  void draw_tetromino(SDL_Renderer &renderer, Tetromino tetromino,
                      TetrominoRenderType render_type, Point<float> offset);

  void draw_matrix(SDL_Renderer &renderer, const Matrix &matrix);

  float tile_size_{};
};
