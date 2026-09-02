#pragma once

// An ordered pair of type `float`
struct FPoint {
  float x, y;
};

namespace fpoint {
[[nodiscard]] auto add(FPoint a, FPoint b) -> FPoint;
[[nodiscard]] auto subtract(FPoint a, FPoint b) -> FPoint;
[[nodiscard]] auto multiply_scalar(FPoint a, float scalar) -> FPoint;
} // namespace fpoint
