#ifndef IRENDER_HPP
#define IRENDER_HPP
#include <cstdint>
#include <span>

struct RectF {
  float x, y, w, h;
};

struct Color {
  uint8_t r, g, b, a;
};

class IRenderer {
public:
  virtual bool initialized() const = 0;

  virtual void clear() = 0;

  virtual void present() = 0;

  virtual void set_color(Color color) = 0;

  virtual void render_rects(std::span<RectF> rects) = 0;

  virtual void render_fill_rects(std::span<RectF> rects) = 0;

  virtual ~IRenderer() = default;
};

#endif
