#ifndef TETRIS_RENDERER_HPP
#define TETRIS_RENDERER_HPP
#include "IRenderer.hpp"
#include "Tetris.hpp"

enum class Fill { Solid, Transparent, None };
enum class Outline : bool { Disabled = false, Enabled = true };

class TetrisRenderer {
public:
  explicit TetrisRenderer(IRenderer &render_backend, float tile_size = 40)
      : renderer_(render_backend), tile_size_(tile_size) {}

  TetrisRenderer(const TetrisRenderer &) = delete;
  TetrisRenderer &operator=(const TetrisRenderer &) = delete;

  void adjust_offset(int win_w, int win_h);

  void draw_frame(const Tetris &tetris);

private:
  void draw_matrix(const Matrix &matrix);

  void draw_next_queue(const NextQueue &queue);

  void draw_tetromino(const Tetromino &tet, Point offset, Fill fill,
                      Outline outline);

  void draw_grounded_tiles(const Matrix &matrix);

  void draw_matrix_outline();

  IRenderer &renderer_;

  float tile_size_;

  Point playfield_offset_{0, 0};

  Point next_queue_offset_{0, 0};

  Point hold_offset_{0, 0};
};

#endif
