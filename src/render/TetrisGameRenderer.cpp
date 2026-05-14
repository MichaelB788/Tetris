#include "render/TetrisGameRenderer.hpp"
#include "core/TetrisGame.hpp"
#include "core/Tetris_Move.hpp"
#include "platform/PlatformSDL_IMG.hpp"
#include "render/Tetris_Paint.hpp"
#include <SDL3/SDL_render.h>

TetrisGameRenderer::TetrisGameRenderer(const std::filesystem::path &atlas_path,
                                       SDL_Renderer *renderer)
    : piece_atlas_(sdl::img::create_texture_from_img(renderer, atlas_path)) {
  auto ghost_surf = sdl::img::create_surface_from_img(atlas_path);
  SDL_SetSurfaceAlphaMod(ghost_surf.get(), 0x80);
  ghost_atlas_ = sdl::create_texture_from_surface(renderer, ghost_surf.get());
}

void TetrisGameRenderer::draw_frame(const TetrisGame &game,
                                    SDL_Renderer &renderer) {
  draw_board(game.board(), renderer);
  draw_hud(game.hud(), renderer);
}

void TetrisGameRenderer::draw_board(const Board &board,
                                    SDL_Renderer &renderer) {
  tetris::paint::tetromino(board.player, pos_.board, renderer, *piece_atlas_);

  auto ghost = board.player;
  tetris::move::hard_drop(ghost, board.matrix);
  tetris::paint::tetromino(ghost, pos_.board, renderer, *ghost_atlas_);

  tetris::paint::matrix(board.matrix, pos_.board, renderer, *piece_atlas_);
}

void TetrisGameRenderer::draw_hud(const HUD &hud, SDL_Renderer &renderer) {
  tetris::paint::tetromino(Tetromino(hud.next_queue.peek()), pos_.queue,
                           renderer, *piece_atlas_);

  if (hud.held_type.has_value()) {
    tetris::paint::tetromino(Tetromino(hud.held_type.value()), pos_.hold,
                             renderer, *piece_atlas_);
  }
}

void TetrisGameRenderer::align_inside_rect(std::pair<int, int> rect) {
  auto &[board_x, board_y] = pos_.board;
  auto &[queue_x, queue_y] = pos_.queue;
  auto &[hold_x, hold_y] = pos_.hold;

  const auto [w, h] = rect;
  board_x = (w - (Matrix::COLS * TILE_SIZE)) / 2;
  board_y = (h - (Matrix::ROWS * TILE_SIZE)) / 2;

  queue_x = board_x - (4 * TILE_SIZE);

  hold_x = board_x + ((Matrix::COLS + 3) * TILE_SIZE);

  queue_y = hold_y = board_y + TILE_SIZE;
}
