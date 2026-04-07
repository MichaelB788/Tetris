#pragma once
#include "platform/PlatformSDL.hpp"
#include "util/Point.hpp"
#include <filesystem>

class TetrisGame;
struct Board;
struct HUD;

class TetrisGameRenderer {
private:
  struct Positions;

public:
  TetrisGameRenderer(const std::filesystem::path &atlas_path,
                     SDL_Renderer *renderer);

  void draw_frame(const TetrisGame &game, SDL_Renderer &renderer);

  void align_inside_rect(std::pair<int, int> rect);

  [[nodiscard]] auto get_positions() const -> const Positions & { return pos_; }

private:
  void draw_board(const Board &board, SDL_Renderer &renderer);

  void draw_hud(const HUD &hud, SDL_Renderer &renderer);

  struct Positions {
    Point board{.x = 0, .y = 0};

    Point queue{.x = 0, .y = 0};

    Point hold{.x = 0, .y = 0};
  } pos_;

  sdl::Texture piece_atlas_ = nullptr;

  sdl::Texture ghost_atlas_ = nullptr;
};
