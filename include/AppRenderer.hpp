#pragma once
#include "PlatformSDL.hpp"
#include "Point.hpp"
#include "Tetromino.hpp"
#include "TextRenderer.hpp"
#include <cstdint>
#include <filesystem>

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

  void draw_game_objects(const Tetris &tetris) const;
  void draw_screen_text(const Tetris &tetris);
  void draw_pause_menu() const;

  Point<float> section_matrix_{};
  Point<float> section_left_{};
  Point<float> section_right_{};

  SDL::Window window_ = nullptr;
  SDL::Renderer renderer_ = nullptr;
  SDL::Texture texture_atlas_ = nullptr;

  TextRenderer text_renderer_;
};
