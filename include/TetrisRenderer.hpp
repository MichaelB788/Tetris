#pragma once
#include "Geometry.hpp"
#include "GraphicsContext.hpp"
#include "Piece.hpp"
#include <filesystem>

class Tetris;
class Playfield;

class TetrisRenderer {
public:
  TetrisRenderer(const std::filesystem::path &atlas_texture_path,
                 const std::filesystem::path &font_path);

  void update_on_resize();

  void render_frame(const Tetris &tetris) const;

private:
  enum class BlockStyle { Solid, Ghost };

  struct Layout {
    Point playfield{}, preview{}, held{};
  };

  void draw_block(Piece::Type type, Point pos,
                  BlockStyle style = BlockStyle::Solid) const;
  void draw_piece(Piece piece, Point base_pos,
                  BlockStyle style = BlockStyle::Solid) const;
  void draw_playfield(const Playfield &playfield, Point base_pos) const;

  void draw_number(unsigned uint, Point pos) const;
  void draw_text(TTF_Text &text, Point pos) const;
  void draw_text_centered(TTF_Text &text) const;

  Layout layout{};
  GraphicsContext ctx;
};
