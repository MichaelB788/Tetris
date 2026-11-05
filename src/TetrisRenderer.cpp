#include "TetrisRenderer.hpp"
#include "Geometry.hpp"
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
constexpr float PLAYFIELD_PIXL_WIDTH = Playfield::COLS * PIXL_SZ;
constexpr float PLAYFIELD_PIXL_HEIGHT = Playfield::ROWS * PIXL_SZ;

auto resolve(Point base, Vector offset) -> Point {
  return base + (offset * PIXL_SZ);
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

  window.base_pos.playfield.x = (window.size.w - PLAYFIELD_PIXL_WIDTH) / 2;
  window.base_pos.playfield.y = (window.size.h - PLAYFIELD_PIXL_HEIGHT) / 2;
  window.base_pos.left = resolve(window.base_pos.playfield, {-6, 0});
  window.base_pos.right =
      resolve(window.base_pos.playfield, {Playfield::COLS + 2, 0});
}

void TetrisRenderer::render_frame(const Tetris &tetris) const {
  SDL_SetRenderDrawColor(ctx.renderer.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(ctx.renderer.get());

  switch (tetris.get_state()) {
  case Tetris::State::Running:
    // draw pieces
    draw_piece(tetris.get_active_piece(), window.base_pos.playfield);
    draw_piece(tetris.get_ghost_piece(), window.base_pos.playfield,
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

    // draw playfield
    draw_playfield(tetris.get_playfield(), window.base_pos.playfield);

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

void TetrisRenderer::draw_block(Piece::Type type, Point pos,
                                BlockStyle style) const {
  const auto src_y_offset = style == BlockStyle::Ghost ? PIXL_SZ : 0;
  const auto src_rect = SDL_FRect{PIXL_SZ * static_cast<float>(type),
                                  src_y_offset, PIXL_SZ, PIXL_SZ};
  const auto dst_rect = SDL_FRect{pos.x, pos.y, PIXL_SZ, PIXL_SZ};
  SDL_RenderTexture(ctx.renderer.get(), ctx.piece_atlas.get(), &src_rect,
                    &dst_rect);
}

void TetrisRenderer::draw_piece(Piece piece, Point base,
                                BlockStyle style) const {
  for (const auto pos : piece.get_shape()) {
    draw_block(piece.get_type(), resolve(base, {pos.x, pos.y}), style);
  }
}

void TetrisRenderer::draw_playfield(const Playfield &playfield,
                                    Point base) const {
  for (size_t y = 0; y < Playfield::ROWS; ++y) {
    for (size_t x = 0; x < Playfield::COLS; ++x) {
      if (const auto cell = playfield(x, y))
        draw_block(
            cell.value(),
            resolve(base, {static_cast<float>(x), static_cast<float>(y)}),
            BlockStyle::Solid);
    }
  }

  const auto playfield_outline_rect =
      SDL_FRect{base.x, base.y, PLAYFIELD_PIXL_WIDTH, PLAYFIELD_PIXL_HEIGHT};
  SDL_SetRenderDrawColor(ctx.renderer.get(), 0x54, 0x58, 0xCC, 0xFF);
  SDL_RenderRect(ctx.renderer.get(), &playfield_outline_rect);
}

void TetrisRenderer::draw_uint(unsigned n, Point pos) const {
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

void TetrisRenderer::draw_text(GameText game_text, Point pos) const {
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
