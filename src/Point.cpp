#include "Point.hpp"

auto fpoint::add(FPoint a, FPoint b) -> FPoint {
  return {a.x + b.x, a.y + b.y};
}

auto fpoint::subtract(FPoint a, FPoint b) -> FPoint {
  return {a.x - b.x, a.y - b.y};
}

auto fpoint::multiply_scalar(FPoint a, float scalar) -> FPoint {
  return {a.x * scalar, a.y * scalar};
}
