#pragma once
#include "PlatformSDL.hpp"
#include "Tetris.hpp"
#include <filesystem>

class GameRenderer {
public:
  struct GameLayout {
    Point<float> board{};
    Point<float> queue{};
    Point<float> hold{};
  };
  struct HudLayout {
    Point<float> next_label{};
    Point<float> hold_label{};
    Point<float> score_label{};
    Point<float> score_value{};
    Point<float> fps_label{};
    Point<float> fps_value{};
  };

  GameRenderer(SDL_Renderer &renderer, const std::filesystem::path &atlas_path,
               float tile_size = 32);

  void draw_snapshot(SDL_Renderer &renderer, const Tetris::Snapshot &game);

  void fit_within_window(SDL_Window &window);

  auto get_game_layout() const -> GameLayout { return game_layout; }

  auto compute_hud_layout() const -> HudLayout;

private:
  auto resolve(Point<float> base, Point<float> offset) const -> Point<float> {
    return base + (offset * tile_size_);
  }

  enum class TetrominoRenderType { Ghost, Normal };
  void draw_tetromino_tile(SDL_Renderer &renderer, Tetromino::Type type,
                           TetrominoRenderType render_type,
                           Point<int> tetromino_pos, Point<float> offset);

  void draw_tetromino(SDL_Renderer &renderer, Tetromino tetromino,
                      TetrominoRenderType render_type, Point<float> offset);

  void draw_matrix(SDL_Renderer &renderer, const Matrix &matrix);

  float tile_size_{};
  GameLayout game_layout{};
};
