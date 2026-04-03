#pragma once
#include "platform/PlatformSDL.hpp"
#include "render/Tetris_Paint.hpp"
#include "util/Point.hpp"

class Matrix;
class Board;
class Tetromino;

class BoardRenderer {
public:
  BoardRenderer(const std::filesystem::path &path_to_atlas,
                SDL_Renderer &renderer);

  void draw_board(const Board &board);

  void center_within_window(int win_w, int win_h);

  [[nodiscard]] Point pos() const { return board_pos_; }

private:
  void draw_matrix_outline();

  SDL_Renderer &renderer_;

  PlatformSDL::Texture atlas_{};

  PlatformSDL::Texture ghost_atlas_{};

  Point board_pos_{0, 0};
};
