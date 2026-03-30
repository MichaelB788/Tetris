#pragma once
#include "platform/PlatformSDL.hpp"
#include "util/Point.hpp"
#include <array>

class TextRenderer {
public:
  TextRenderer(const std::filesystem::path &font_path, int font_size,
               SDL_Renderer &renderer);

  void render_text();

  void render_scores(unsigned score, unsigned high_score);

  void adjust_lhs(Point queue_pos);

  void adjust_rhs(Point hold_pos);

private:
  PlatformSDL::Text create_text(const char *str) const;

private:
  struct TextTexture {
    PlatformSDL::Text text{};
    float x{}, y{};
  };

  SDL_Renderer &renderer_;

  PlatformSDL::TextEngine text_engine_{};

  PlatformSDL::Font font_{};

  enum TextIndex { SCORE, MAX_SCORE, NEXT, HOLD, COUNT };

  std::array<TextTexture, COUNT> textures_{};

  std::array<PlatformSDL::Text, 10> nums_{};
};
