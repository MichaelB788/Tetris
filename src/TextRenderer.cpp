#include "TextRenderer.hpp"
#include "SDL3_ttf/SDL_ttf.h"
#include "pixel.hpp"

TextRenderer::TextRenderer(const std::filesystem::path &font_path,
                           int font_size, SDL_Renderer *renderer)
    : renderer_(renderer),
      text_engine_(PlatformSDL::create_renderer_text_engine(renderer_)),
      font_(PlatformSDL::open_font(font_path, font_size)) {
  text_[SCORE] = {
      PlatformSDL::create_text(text_engine_.get(), font_.get(), "Score")};

  text_[MAX_SCORE] = {
      PlatformSDL::create_text(text_engine_.get(), font_.get(), "High")};

  text_[NEXT] = {
      PlatformSDL::create_text(text_engine_.get(), font_.get(), "Next")};

  text_[HOLD] = {
      PlatformSDL::create_text(text_engine_.get(), font_.get(), "Hold")};

  for (unsigned i = 0; i < nums_.size(); ++i)
    nums_[i] = PlatformSDL::create_text(text_engine_.get(), font_.get(),
                                        std::to_string(i).c_str());
}

void TextRenderer::render_text() {
  for (auto &texture : text_)
    TTF_DrawRendererText(texture.text.get(), texture.x, texture.y);
}

void TextRenderer::render_score(unsigned score) {
  float x = text_[SCORE].x;
  float y = text_[SCORE].y + pixel::SIZE * 2;

  std::array<unsigned, 3> digit{};
  for (int i = digit.size() - 1; i >= 0; --i) {
    digit[i] = score % 10;
    score /= 10;
  }

  for (std::size_t i = 0; i < digit.size(); ++i) {
    TTF_DrawRendererText(nums_[digit[i]].get(), x, y);
    x += 40;
  }
}

void TextRenderer::adjust_lhs(Point queue_pos) {
  text_[NEXT].x = queue_pos.x - pixel::SIZE;
  text_[NEXT].y = queue_pos.y - pixel::SIZE * 3;
}

void TextRenderer::adjust_rhs(Point hold) {
  text_[SCORE].x = text_[MAX_SCORE].x = text_[HOLD].x = hold.x - pixel::SIZE;
  text_[HOLD].y = hold.y - pixel::SIZE * 3;
  text_[SCORE].y = hold.y + pixel::SIZE * 4;
  text_[MAX_SCORE].y = hold.y + pixel::SIZE * 11;
}
