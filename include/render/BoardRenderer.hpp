#pragma once
#include "platform/PlatformSDL.hpp"
#include "util/Point.hpp"

class Matrix;
class Tetromino;

class BoardRenderer {
public:
  BoardRenderer(const std::filesystem::path &path_to_atlas,
                SDL_Renderer &renderer);

  void draw_current(const Tetromino &current);

  void draw_ghost(const Tetromino &ghost);

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
