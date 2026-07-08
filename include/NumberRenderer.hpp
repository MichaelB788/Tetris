#pragma once
#include "PlatformSDL_TTF.hpp"
#include "Point.hpp"
#include <array>

class NumberRenderer {
public:
  explicit NumberRenderer(TTF_TextEngine *engine, TTF_Font *font);

  void render_num(int num, Point<float> pos) const;

private:
  std::array<SDL::TTF::Text, 10> nums_text_{};
};
