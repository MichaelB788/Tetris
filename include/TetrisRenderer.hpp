#pragma once
#include "Geometry.hpp"
#include "Piece.hpp"
#include "PlatformSDL.hpp"
#include "PlatformSDL_TTF.hpp"
#include <array>
#include <filesystem>
#include <string_view>

class Tetris;
class Playfield;

class TetrisRenderer {
public:
  // Throws an SDL::Exception upon failure
  TetrisRenderer(const std::filesystem::path &atlas_texture_path,
                 const std::filesystem::path &font_path);

  void update_layout_on_resize();

  void render_frame(const Tetris &tetris) const;

private:
  enum class BlockStyle { Solid, Ghost };

  struct Layout {
    Point playfield{}, preview{}, held{};
  };

  struct GameText {
    SDL::TTF::Text next{}, held{}, score{}, paused{}, game_over{};
  };

  [[nodiscard]] auto make_text(std::string_view text) const -> SDL::TTF::Text;

  void draw_block(Piece::Type type, Point pos,
                  BlockStyle style = BlockStyle::Solid) const;
  void draw_piece(Piece piece, Point base_pos,
                  BlockStyle style = BlockStyle::Solid) const;
  void draw_playfield(const Playfield &playfield, Point base_pos) const;

  void draw_number(unsigned uint, Point pos) const;
  void draw_text(TTF_Text &text, Point pos) const;
  void draw_text_centered(TTF_Text &text) const;

  Layout layout{};

  SDL::Display display{};
  SDL::Texture piece_atlas{};

  SDL::TTF::RendererTextEngine engine{};
  SDL::TTF::Font font{};
  GameText game_text{};
  std::array<SDL::TTF::Text, 10> digit_text{};
};
