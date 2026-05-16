#pragma once
#include "platform/PlatformSDL_TTF.hpp"
#include "util/Point.hpp"
#include <array>
#include <filesystem>

class TetrisGameRenderer;

class TextRenderer {
public:
  TextRenderer(const std::filesystem::path &font_path, int font_size,
               SDL_Renderer *renderer);

  void render_screen_text();

  void render_score_int(int score);

  void align_with_game(const TetrisGameRenderer &game_renderer);

private:
  struct TextObj {
    Text text = nullptr;
    Point<float> pos{};
  };
  void render_text(const TextObj &renderer);

  RendererTextEngine text_engine_ = nullptr;
  Font font_ = nullptr;

  TextObj next_{};
  TextObj stored_{};
  TextObj hold_{};
  TextObj score_{};

  std::array<Text, 10> nums_{};
};
