#pragma once
#include "platform/PlatformSDL_TTF.hpp"
#include <array>

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
    sdl::ttf::Text text = nullptr;
    std::pair<float, float> pos{};
  };

  void render_text(const TextObj &renderer);

  sdl::ttf::RendererTextEngine text_engine_ = nullptr;

  sdl::ttf::Font font_ = nullptr;

  struct ScreenText {
    TextObj next_{};

    TextObj stored_{};

    TextObj hold_{};

    TextObj score_{};
  } screen_text_;

  std::array<sdl::ttf::Text, 10> nums_{};
};
