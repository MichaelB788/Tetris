#include "render/TextRenderer.hpp"
#include "SDL3_ttf/SDL_ttf.h"
#include "render/tetris-paint.hpp"
#include <cstddef>
#include <vector>

TextRenderer::TextRenderer(const std::filesystem::path &font_path,
                           int font_size, SDL_Renderer &renderer)
    : renderer_(renderer),
      text_engine_(PlatformSDL::create_renderer_text_engine(renderer_)),
      font_(PlatformSDL::open_font(font_path, font_size)) {
  textures_[SCORE] = {.text = create_text("Score")};
  textures_[NEXT] = {.text = create_text("Next")};
  textures_[HOLD] = {.text = create_text("Hold")};

  for (unsigned i = 0; i < nums_.size(); ++i)
    nums_[i] = PlatformSDL::create_text(*text_engine_, *font_,
                                        std::to_string(i).c_str());
}

void TextRenderer::render_text() {
  for (auto &texture : textures_)
    TTF_DrawRendererText(texture.text.get(), texture.x, texture.y);
}

void TextRenderer::render_score(int score) {
  float score_x = textures_[SCORE].x;
  float score_y = textures_[SCORE].y + tetris::paint::TILE_SIZE * 2;

  int offset_x;
  TTF_GetTextSize(nums_[0].get(), &offset_x, NULL);

  std::vector<int> score_digits{};

  while (score > 0) {
    score_digits.push_back(score % 10);
    score /= 10;
  }

  while (!score_digits.empty()) {
    TTF_DrawRendererText(nums_[score_digits.back()].get(), score_x, score_y);
    score_digits.pop_back();
    score_x += offset_x;
  }
}

void TextRenderer::adjust_lhs(Point queue_pos) {
  textures_[NEXT].x = queue_pos.x - tetris::paint::TILE_SIZE;
  textures_[NEXT].y = queue_pos.y - tetris::paint::TILE_SIZE * 3;
}

void TextRenderer::adjust_rhs(Point hold) {
  textures_[SCORE].x = textures_[HOLD].x = hold.x - tetris::paint::TILE_SIZE;
  textures_[HOLD].y = hold.y - tetris::paint::TILE_SIZE * 3;
  textures_[SCORE].y = hold.y + tetris::paint::TILE_SIZE * 4;
}

PlatformSDL::Text TextRenderer::create_text(const char *str) const {
  return PlatformSDL::create_text(*text_engine_, *font_, str);
}
