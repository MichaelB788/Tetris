#include "TextRenderer.hpp"
#include "SDL3_ttf/SDL_ttf.h"
#include "pixel.hpp"

TextRenderer::TextRenderer(const std::filesystem::path &font_path,
                           int font_size, SDL_Renderer &renderer)
    : renderer_(renderer),
      text_engine_(PlatformSDL::create_renderer_text_engine(renderer_)),
      font_(PlatformSDL::open_font(font_path, font_size)) {
  textures_[SCORE] = {PlatformSDL::create_text(*text_engine_, *font_, "Score")};

  textures_[MAX_SCORE] = {
      PlatformSDL::create_text(*text_engine_, *font_, "Best")};

  textures_[NEXT] = {PlatformSDL::create_text(*text_engine_, *font_, "Next")};

  textures_[HOLD] = {PlatformSDL::create_text(*text_engine_, *font_, "Hold")};

  for (unsigned i = 0; i < nums_.size(); ++i)
    nums_[i] = PlatformSDL::create_text(*text_engine_, *font_,
                                        std::to_string(i).c_str());
}

void TextRenderer::render_text() {
  for (auto &texture : textures_)
    TTF_DrawRendererText(texture.text.get(), texture.x, texture.y);
}

void TextRenderer::render_scores(unsigned score, unsigned max_score) {
  static constexpr std::size_t max_digits = 4;

  float shared_x = textures_[SCORE].x;
  float score_y = textures_[SCORE].y + pixel::SIZE * 2;
  float max_score_y = textures_[MAX_SCORE].y + pixel::SIZE * 2;

  int offset_x;
  TTF_GetTextSize(nums_[0].get(), &offset_x, NULL);

  std::array<unsigned, 4> score_digits{};
  std::array<unsigned, 4> max_score_digits{};

  for (int i = max_digits - 1; i >= 0; --i) {
    score_digits[i] = score % 10;
    max_score_digits[i] = max_score % 10;

    score /= 10;
    max_score /= 10;
  }

  for (std::size_t i = 0; i < max_digits; ++i) {
    if (i == max_digits - 1 || score_digits[i] > 0)
      TTF_DrawRendererText(nums_[score_digits[i]].get(), shared_x, score_y);

    if (i == max_digits - 1 || max_score_digits[i] > 0)
      TTF_DrawRendererText(nums_[max_score_digits[i]].get(), shared_x,
                           max_score_y);
    shared_x += offset_x;
  }
}

void TextRenderer::adjust_lhs(Point queue_pos) {
  textures_[NEXT].x = queue_pos.x - pixel::SIZE;
  textures_[NEXT].y = queue_pos.y - pixel::SIZE * 3;
}

void TextRenderer::adjust_rhs(Point hold) {
  textures_[SCORE].x = textures_[MAX_SCORE].x = textures_[HOLD].x =
      hold.x - pixel::SIZE;
  textures_[HOLD].y = hold.y - pixel::SIZE * 3;
  textures_[SCORE].y = hold.y + pixel::SIZE * 4;
  textures_[MAX_SCORE].y = hold.y + pixel::SIZE * 11;
}
