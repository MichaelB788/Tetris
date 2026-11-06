#include "TetrisRenderer.hpp"
#include "Geometry.hpp"
#include "GraphicsContext.hpp"
#include "Piece.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <vector>

namespace {
constexpr float PLAYFIELD_PIXEL_W = Playfield::COLS * PIXEL_SCALE;
constexpr float PLAYFIELD_PIXEL_H = Playfield::ROWS * PIXEL_SCALE;

auto resolve(Point origin, Vector offset) -> Point {
  return origin + (offset * PIXEL_SCALE);
}
} // namespace

TetrisRenderer::TetrisRenderer(const std::filesystem::path &atlas_texture_path,
                               const std::filesystem::path &font_path)
    : ctx(atlas_texture_path, font_path) {
  update_on_resize();
}

void TetrisRenderer::update_on_resize() {
  ctx.update_window_size();

  layout.playfield.x =
      (static_cast<float>(ctx.window_size.w) - PLAYFIELD_PIXEL_W) / 2;
  layout.playfield.y =
      (static_cast<float>(ctx.window_size.h) - PLAYFIELD_PIXEL_H) / 2;

  layout.queue = resolve(layout.playfield, {-6, 0});
  layout.held = resolve(layout.playfield, {Playfield::COLS + 2, 0});
}

void TetrisRenderer::render_frame(const Tetris &tetris) const {
  SDL_SetRenderDrawColor(ctx.renderer.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(ctx.renderer.get());

  switch (tetris.get_state()) {
  case Tetris::State::Running:
    // draw pieces
    draw_piece(tetris.get_active_piece(), layout.playfield);
    draw_piece(tetris.get_ghost_piece(), layout.playfield, BlockStyle::Ghost);

    if (const auto held_type = tetris.get_held_piece_type())
      draw_piece({held_type.value()}, resolve(layout.held, {1, 3}));

    // draw next queue
    {
      const auto preview = tetris.get_seven_bag_preview();
      for (size_t i = 0; i < preview.size(); ++i) {
        draw_piece({preview[i]},
                   resolve(layout.queue, {1, 3 * static_cast<float>(i + 1)}));
      }
    }

    // draw playfield
    draw_playfield(tetris.get_playfield(), layout.playfield);

    // draw text
    draw_text(GameText::Next, layout.queue);
    draw_text(GameText::Hold, layout.held);
    draw_text(GameText::Score, resolve(layout.held, {0, 8}));
    draw_number(tetris.get_score(), resolve(layout.held, {0, 10}));
    break;
  case Tetris::State::Paused:
    draw_text_centered(GameText::Paused);
    break;
  case Tetris::State::GameOver:
    draw_text_centered(GameText::GameOver);
    break;
  }

  SDL_RenderPresent(ctx.renderer.get());
}

void TetrisRenderer::draw_block(Piece::Type type, Point pos,
                                BlockStyle style) const {
  const auto src_y_offset = style == BlockStyle::Ghost ? PIXEL_SCALE : 0;
  const auto src_rect = SDL_FRect{PIXEL_SCALE * static_cast<float>(type),
                                  src_y_offset, PIXEL_SCALE, PIXEL_SCALE};
  const auto dst_rect = SDL_FRect{pos.x, pos.y, PIXEL_SCALE, PIXEL_SCALE};
  SDL_RenderTexture(ctx.renderer.get(), ctx.piece_atlas.get(), &src_rect,
                    &dst_rect);
}

void TetrisRenderer::draw_piece(Piece piece, Point origin,
                                BlockStyle style) const {
  for (const auto pos : piece.get_shape()) {
    draw_block(piece.get_type(), resolve(origin, {pos.x, pos.y}), style);
  }
}

void TetrisRenderer::draw_playfield(const Playfield &playfield,
                                    Point origin) const {
  for (size_t y = 0; y < Playfield::ROWS; ++y) {
    for (size_t x = 0; x < Playfield::COLS; ++x) {
      if (const auto cell = playfield(x, y))
        draw_block(
            cell.value(),
            resolve(origin, {static_cast<float>(x), static_cast<float>(y)}),
            BlockStyle::Solid);
    }
  }

  const SDL_FRect playfield_outline{origin.x, origin.y, PLAYFIELD_PIXEL_W,
                                    PLAYFIELD_PIXEL_H};
  SDL_SetRenderDrawColor(ctx.renderer.get(), 0x54, 0x58, 0xCC, 0xFF);
  SDL_RenderRect(ctx.renderer.get(), &playfield_outline);
}

void TetrisRenderer::draw_number(unsigned n, Point pos) const {
  if (n < 10) {
    TTF_DrawRendererText(ctx.digit_text[n].get(), pos.x, pos.y);
    return;
  }

  std::vector<unsigned> digits{};
  while (n > 0) {
    digits.push_back(n % 10);
    n /= 10;
  }

  while (!digits.empty()) {
    TTF_DrawRendererText(ctx.digit_text[digits.back()].get(), pos.x, pos.y);
    digits.pop_back();
    pos.x += PIXEL_SCALE;
  }
}

void TetrisRenderer::draw_text(GameText game_text, Point pos) const {
  TTF_DrawRendererText(ctx.game_text[game_text].get(), pos.x, pos.y);
}

void TetrisRenderer::draw_text_centered(GameText game_text) const {
  Size text{};
  TTF_GetTextSize(ctx.game_text[game_text].get(), &text.w, &text.h);
  TTF_DrawRendererText(ctx.game_text[game_text].get(),
                       (ctx.window_size.w - static_cast<float>(text.w)) / 2,
                       (ctx.window_size.h - static_cast<float>(text.h)) / 2);
}
