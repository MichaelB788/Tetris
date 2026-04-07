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
  tetris::paint::tetromino(board.player, renderer, *piece_atlas_, pos_.board);

  Tetromino ghost = tetris::move::compute_dropped(board.player, board.matrix);
  tetris::paint::tetromino(ghost, renderer, *ghost_atlas_, pos_.board);

  tetris::paint::matrix(board.matrix, renderer, *piece_atlas_, pos_.board);
}

void TetrisGameRenderer::draw_hud(const HUD &hud, SDL_Renderer &renderer) {
  tetris::paint::tetromino(Tetromino(hud.next_queue.peek()), renderer,
                           *piece_atlas_, pos_.queue);

  if (hud.held_type.has_value()) {
    tetris::paint::tetromino(Tetromino(hud.held_type.value()), renderer,
                             *piece_atlas_, pos_.hold);
  }
}

void TetrisGameRenderer::align_inside_rect(std::pair<int, int> rect) {
  auto &[board_x, board_y] = pos_.board;
  auto &[queue_x, queue_y] = pos_.queue;
  auto &[hold_x, hold_y] = pos_.hold;

  const auto [w, h] = rect;
  board_x = (w - (Matrix::COLS * tetris::paint::TILE_SIZE)) / 2;
  board_y = (h - (Matrix::ROWS * tetris::paint::TILE_SIZE)) / 2;

  queue_x = board_x - (4 * tetris::paint::TILE_SIZE);

  hold_x = board_x + ((Matrix::COLS + 3) * tetris::paint::TILE_SIZE);

  queue_y = hold_y = board_y + tetris::paint::TILE_SIZE;
}
