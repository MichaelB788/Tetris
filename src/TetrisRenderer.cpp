#include "TetrisRenderer.hpp"
#include "FPoint.hpp"
#include "GraphicsContext.hpp"
#include "Piece.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <stack>
#include <vector>

namespace {
constexpr float MATRIX_PIXL_WIDTH = Matrix::COLS * PIXL_SZ;
constexpr float MATRIX_PIXL_HEIGHT = Matrix::ROWS * PIXL_SZ;

auto resolve(FPoint base, FPoint offset) -> FPoint {
  return fpoint::add(base, fpoint::multiply_scalar(offset, PIXL_SZ));
}
} // namespace

TetrisRenderer::TetrisRenderer(const std::filesystem::path &atlas_texture_path,
                               const std::filesystem::path &font_path)
    : ctx(atlas_texture_path, font_path) {
  update_resized_window_layout();
}

void TetrisRenderer::update_resized_window_layout() {
  // Update window size
  int w, h;
  SDL_GetWindowSize(ctx.window.get(), &w, &h);
  window.size.w = static_cast<float>(w);
  window.size.h = static_cast<float>(h);

  window.base_pos.matrix.x = (window.size.w - MATRIX_PIXL_WIDTH) / 2;
  window.base_pos.matrix.y = (window.size.h - MATRIX_PIXL_HEIGHT) / 2;
  window.base_pos.left = resolve(window.base_pos.matrix, {-6, 0});
  window.base_pos.right =
      resolve(window.base_pos.matrix, {Matrix::COLS + 2, 0});
}

void TetrisRenderer::render_frame(const Tetris &tetris) const {
  SDL_SetRenderDrawColor(ctx.renderer.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(ctx.renderer.get());

  switch (tetris.get_state()) {
  case Tetris::State::Running:
    // draw pieces
    draw_piece(tetris.get_active_piece(), window.base_pos.matrix);
    draw_piece(tetris.get_ghost_piece(), window.base_pos.matrix,
               BlockStyle::Ghost);

    if (const auto held_type = tetris.get_held_piece_type())
      draw_piece({held_type.value()}, resolve(window.base_pos.right, {1, 3}));

    // draw next queue
    {
      const auto preview = tetris.get_seven_bag_preview();
      for (size_t i = 0; i < preview.size(); ++i) {
        draw_piece({preview[i]}, resolve(window.base_pos.left,
                                         {1, 3 * static_cast<float>(i + 1)}));
      }
    }

    // draw matrix
    draw_matrix(tetris.get_matrix(), window.base_pos.matrix);

    // draw text
    draw_text(GameText::Next, window.base_pos.left);
    draw_text(GameText::Hold, window.base_pos.right);
    draw_text(GameText::Score, resolve(window.base_pos.right, {0, 8}));
    draw_uint(tetris.get_score(), resolve(window.base_pos.right, {0, 10}));
    break;
  case Tetris::State::Paused:
    draw_centered_text(GameText::Paused);
    break;
  case Tetris::State::GameOver:
    draw_centered_text(GameText::GameOver);
    break;
  }

  SDL_RenderPresent(ctx.renderer.get());
}

void TetrisRenderer::draw_block(Piece::Type type, FPoint pos,
                                BlockStyle style) const {
  const auto src_y_offset = style == BlockStyle::Ghost ? PIXL_SZ : 0;
  const auto src_rect = SDL_FRect{PIXL_SZ * static_cast<float>(type),
                                  src_y_offset, PIXL_SZ, PIXL_SZ};
  const auto dst_rect = SDL_FRect{pos.x, pos.y, PIXL_SZ, PIXL_SZ};
  SDL_RenderTexture(ctx.renderer.get(), ctx.piece_atlas.get(), &src_rect,
                    &dst_rect);
}

void TetrisRenderer::draw_piece(Piece piece, FPoint base,
                                BlockStyle style) const {
  for (const auto pos : piece.get_shape())
    draw_block(piece.type, resolve(base, pos), style);
}

void TetrisRenderer::draw_matrix(const Matrix &matrix, FPoint base) const {
  for (size_t y = 0; y < Matrix::ROWS; ++y) {
    for (size_t x = 0; x < Matrix::COLS; ++x) {
      const auto fpos = FPoint{static_cast<float>(x), static_cast<float>(y)};
      if (auto tile = matrix.at(fpos))
        draw_block(tile.value(), resolve(base, fpos), BlockStyle::Solid);
    }
  }

  const auto matrix_outline_rect =
      SDL_FRect{base.x, base.y, MATRIX_PIXL_WIDTH, MATRIX_PIXL_HEIGHT};
  SDL_SetRenderDrawColor(ctx.renderer.get(), 0x54, 0x58, 0xCC, 0xFF);
  SDL_RenderRect(ctx.renderer.get(), &matrix_outline_rect);
}

void TetrisRenderer::draw_uint(unsigned n, FPoint pos) const {
  if (n < 10) {
    TTF_DrawRendererText(ctx.uint_text_map[n].get(), pos.x, pos.y);
    return;
  }

  std::stack<unsigned, std::vector<unsigned>> digits{};
  while (n > 0) {
    digits.push(n % 10);
    n /= 10;
  }

  while (!digits.empty()) {
    TTF_DrawRendererText(ctx.uint_text_map[digits.top()].get(), pos.x, pos.y);
    digits.pop();
    pos.x += PIXL_SZ;
  }
}

void TetrisRenderer::draw_text(GameText game_text, FPoint pos) const {
  TTF_DrawRendererText(ctx.game_text_map[static_cast<size_t>(game_text)].get(),
                       pos.x, pos.y);
}

void TetrisRenderer::draw_centered_text(GameText i) const {
  int text_w, text_h;
  TTF_GetTextSize(ctx.game_text_map[static_cast<size_t>(i)].get(), &text_w,
                  &text_h);
  TTF_DrawRendererText(ctx.game_text_map[static_cast<size_t>(i)].get(),
                       (window.size.w - static_cast<float>(text_w)) / 2,
                       (window.size.h - static_cast<float>(text_h)) / 2);
}
