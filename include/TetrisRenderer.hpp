#pragma once
#include "FPoint.hpp"
#include "FSize.hpp"
#include "GraphicsContext.hpp"
#include "Piece.hpp"
#include <filesystem>

class Tetris;
class Matrix;

class TetrisRenderer {
public:
  TetrisRenderer(const std::filesystem::path &atlas_texture_path,
                 const std::filesystem::path &font_path);

  void update_resized_window_layout();

  void render_frame(const Tetris &tetris) const;

private:
  enum class BlockStyle { Solid, Ghost };

  void draw_block(Piece::Type type, FPoint pos,
                  BlockStyle style = BlockStyle::Solid) const;
  void draw_piece(Piece piece, FPoint base_pos,
                  BlockStyle style = BlockStyle::Solid) const;
  void draw_matrix(const Matrix &matrix, FPoint base_pos) const;

  void draw_uint(unsigned uint, FPoint pos) const;
  void draw_text(GameText game_text, FPoint pos) const;
  void draw_centered_text(GameText game_text) const;

  struct {
    FSize size{};

    struct {
      FPoint matrix{};
      FPoint left{};
      FPoint right{};
    } base_pos;
  } window{};

  GraphicsContext ctx;
};
