#pragma once
#include "PlatformSDL.hpp"
#include "Point.hpp"
#include "Size.hpp"
#include "Tetromino.hpp"
#include "TextRenderer.hpp"
#include <cstdint>
#include <filesystem>
#include <string_view>

class Tetris;
class Matrix;

class AppRenderer {
public:
  AppRenderer(const std::filesystem::path &atlas_path,
              const std::filesystem::path &font_path);

  void center_frame_within_window();

  void render_frame(const Tetris &tetris);

private:
  enum class Style : uint8_t { Filled, Transparent };
  void draw_tile(Tetromino::Type type, Point<float> matrix_base,
                 Point<int> matrix_offset, Style style) const;
  void draw_tetromino(Tetromino tet, Point<float> matrix_base,
                      Style style) const;
  void draw_matrix(const Matrix &matrix, Point<float> matrix_base) const;

  void draw_game_objects(const Tetris &tetris) const;
  void draw_game_text(const Tetris &tetris);
  void draw_centered_text(Msg msg);

  Size<float> win_size{};
  Point<float> section_matrix{};
  Point<float> section_left{};
  Point<float> section_right{};

  SDL::Window window = nullptr;
  SDL::Renderer renderer = nullptr;
  SDL::Texture texture_atlas = nullptr;

  TextRenderer text_renderer;
};
