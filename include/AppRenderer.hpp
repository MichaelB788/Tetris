#pragma once
#include "PlatformSDL.hpp"
#include "PlatformSDL_TTF.hpp"
#include "Point.hpp"
#include "Tetromino.hpp"
#include <array>
#include <cstdint>
#include <filesystem>
#include <string_view>
#include <vector>

class Tetris;
class Matrix;

class AppRenderer {
public:
  AppRenderer(const std::filesystem::path &atlas_path,
              const std::filesystem::path &font_path);

  void center_frame_within_window();

  void render_frame(Tetris &tetris);

private:
  enum class Style : uint8_t { Filled, Transparent };
  void draw_tile(Tetromino::Type type, Point<int> matrix_pos,
                 Point<float> screen_offset, Style style) const;
  void draw_tetromino(Tetromino tet, Point<float> screen_offset,
                      Style style) const;
  void draw_matrix(const Matrix &matrix, Point<float> screen_offset) const;

  void draw_text(std::string_view str, Point<float> pos);
  void draw_num(unsigned num, Point<float> pos) const;

  void draw_game_objects(const Tetris &tetris) const;
  void draw_screen_text(const Tetris &tetris);

  Point<float> section_matrix_{};
  Point<float> section_left_{};
  Point<float> section_right_{};

  SDL::Window window_ = nullptr;
  SDL::Renderer renderer_ = nullptr;
  SDL::Texture texture_atlas_ = nullptr;
  SDL::TTF::RendererTextEngine text_engine_ = nullptr;
  SDL::TTF::Font font_ = nullptr;

  struct TextEntry {
    std::string_view str;
    SDL::TTF::Text texture;
  };
  std::vector<TextEntry> text_map_{};

  std::array<SDL::TTF::Text, 10> nums_text_{};
};
