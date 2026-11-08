#include "TetrisRenderer.hpp"
#include "Geometry.hpp"
#include "Piece.hpp"
#include "PlatformSDL_TTF.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <array>
#include <cstddef>
#include <vector>

namespace {
constexpr float PIXEL_SCALE = 32.0f;
constexpr float PLAYFIELD_PIXEL_W = Playfield::COLS * PIXEL_SCALE;
constexpr float PLAYFIELD_PIXEL_H = Playfield::ROWS * PIXEL_SCALE;

auto resolve(Point origin, Vector offset) -> Point {
  return origin + (offset * PIXEL_SCALE);
}
} // namespace

TetrisRenderer::TetrisRenderer(const std::filesystem::path &atlas_texture_path,
                               const std::filesystem::path &font_path)
    : display("Tetris", 900, 1000, SDL_WINDOW_RESIZABLE),
      piece_atlas(
          SDL::load_texture_from_image(*display.renderer, atlas_texture_path)),
      engine(SDL::TTF::create_renderer_text_engine(*display.renderer)),
      font(SDL::TTF::open_font(font_path, PIXEL_SCALE)),
      game_text{
          make_text("NEXT"),
          make_text("HELD"),
          make_text("SCORE"),
          make_text("PAUSED"),
          make_text("GAME OVER!\n\nCONTINUE?\n\n[Y/N]"),
      },
      digit_text([this]() {
        std::array<SDL::TTF::Text, 10> ret;
        size_t i = 0;
        for (auto n_str : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"})
          ret[i++] = make_text(n_str);
        return ret;
      }()) {
  update_layout_on_resize();
}

void TetrisRenderer::update_layout_on_resize() {
  display.window_resized();

  layout.playfield.x = (static_cast<float>(display.w) - PLAYFIELD_PIXEL_W) / 2;
  layout.playfield.y = (static_cast<float>(display.h) - PLAYFIELD_PIXEL_H) / 2;

  layout.preview = resolve(layout.playfield, {-6, 0});
  layout.held = resolve(layout.playfield, {Playfield::COLS + 2, 0});
}

void TetrisRenderer::render_frame(const Tetris &tetris) const {
  SDL_SetRenderDrawColor(display.renderer.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(display.renderer.get());

  switch (tetris.get_state()) {
  case Tetris::State::Running:
    draw_piece(tetris.get_active_piece(), layout.playfield);
    draw_piece(tetris.get_ghost_piece(), layout.playfield, BlockStyle::Ghost);

    if (const auto held_type = tetris.get_held_piece_type())
      draw_piece(Piece{held_type.value()}, resolve(layout.held, {1, 3}));

    {
      float offset_y = 3;
      for (const auto type : tetris.get_seven_bag_preview()) {
        draw_piece(Piece{type}, resolve(layout.preview, {1, offset_y}));
        offset_y += 3;
      }
    }

    draw_playfield(tetris.get_playfield(), layout.playfield);

    draw_text(*game_text.next, layout.preview);
    draw_text(*game_text.held, layout.held);
    draw_text(*game_text.score, resolve(layout.held, {0, 8}));
    draw_number(tetris.get_score(), resolve(layout.held, {0, 10}));
    break;
  case Tetris::State::Paused:
    draw_text_centered(*game_text.paused);
    break;
  case Tetris::State::GameOver:
    draw_text_centered(*game_text.game_over);
    break;
  }

  SDL_RenderPresent(display.renderer.get());
}

auto TetrisRenderer::make_text(std::string_view text) const -> SDL::TTF::Text {
  return SDL::TTF::create_text(*engine, *font, text);
}

void TetrisRenderer::draw_block(Piece::Type type, Point pos,
                                BlockStyle style) const {
  const auto src_y_offset = style == BlockStyle::Ghost ? PIXEL_SCALE : 0;
  const auto src_rect = SDL_FRect{PIXEL_SCALE * static_cast<float>(type),
                                  src_y_offset, PIXEL_SCALE, PIXEL_SCALE};
  const auto dst_rect = SDL_FRect{pos.x, pos.y, PIXEL_SCALE, PIXEL_SCALE};
  SDL_RenderTexture(display.renderer.get(), piece_atlas.get(), &src_rect,
                    &dst_rect);
}

void TetrisRenderer::draw_piece(const Piece &piece, Point origin,
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
  SDL_SetRenderDrawColor(display.renderer.get(), 0x54, 0x58, 0xCC, 0xFF);
  SDL_RenderRect(display.renderer.get(), &playfield_outline);
}

void TetrisRenderer::draw_number(unsigned number, Point pos) const {
  if (number < 10) {
    draw_text(*digit_text[number], pos);
    return;
  }

  std::vector<unsigned> digits{};
  while (number > 0) {
    digits.push_back(number % 10);
    number /= 10;
  }
  while (!digits.empty()) {
    draw_text(*digit_text[digits.back()], pos);
    digits.pop_back();
    pos.x += PIXEL_SCALE;
  }
}

void TetrisRenderer::draw_text(TTF_Text &text, Point pos) const {
  TTF_DrawRendererText(&text, pos.x, pos.y);
}

void TetrisRenderer::draw_text_centered(TTF_Text &text) const {
  Size text_size{};
  TTF_GetTextSize(&text, &text_size.w, &text_size.h);
  TTF_DrawRendererText(&text, (display.w - static_cast<float>(text_size.w)) / 2,
                       (display.h - static_cast<float>(text_size.h)) / 2);
}
