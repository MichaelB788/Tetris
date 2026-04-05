#include "render/TetrisGameRenderer.hpp"
#include "core/TetrisGame.hpp"
#include "core/Tetris_Move.hpp"
#include "render/Tetris_Paint.hpp"
#include <SDL3/SDL_render.h>

void TetrisGameRenderer::draw_frame(const TetrisGame &game,
                                    SDL_Renderer &renderer,
                                    SDL_Texture &piece_atlas,
                                    SDL_Texture &ghost_atlas) {
  draw_board(game.board(), renderer, piece_atlas, ghost_atlas);
  draw_hud(game.hud(), renderer, piece_atlas);
}

void TetrisGameRenderer::draw_board(const Board &board, SDL_Renderer &renderer,
                                    SDL_Texture &piece_atlas,
                                    SDL_Texture &ghost_atlas) {
  tetris::paint::tetromino(board.player, renderer, piece_atlas, board_pos_);

  Tetromino ghost = tetris::move::compute_dropped(board.player, board.matrix);
  tetris::paint::tetromino(ghost, renderer, ghost_atlas, board_pos_);

  tetris::paint::matrix(board.matrix, renderer, piece_atlas, board_pos_);
}

void TetrisGameRenderer::draw_hud(const HUD &hud, SDL_Renderer &renderer,
                                  SDL_Texture &piece_atlas) {
  tetris::paint::tetromino(Tetromino(hud.next_queue.peek()), renderer,
                           piece_atlas, queue_offset_);

  if (hud.held_type.has_value()) {
    tetris::paint::tetromino(Tetromino(hud.held_type.value()), renderer,
                             piece_atlas, hold_offset_);
  }
}

void TetrisGameRenderer::align_inside_rect(std::pair<int, int> rect) {
  const auto [w, h] = rect;
  board_pos_.x = (w - (Matrix::COLS * tetris::paint::TILE_SIZE)) / 2;
  board_pos_.y = (h - (Matrix::ROWS * tetris::paint::TILE_SIZE)) / 2;

  queue_offset_.x = board_pos_.x - (4 * tetris::paint::TILE_SIZE);
  hold_offset_.x =
      board_pos_.x + ((Matrix::COLS + 3) * tetris::paint::TILE_SIZE);

  queue_offset_.y = hold_offset_.y = board_pos_.y + tetris::paint::TILE_SIZE;
}
