#pragma once
#include <type_traits>

template <typename T>
  requires std::is_arithmetic_v<T>
struct Size {
  T w, h;

  [[nodiscard]] auto operator+(Size other) const -> Size {
    return {w + other.w, h + other.h};
  }
  [[nodiscard]] auto operator-(Size other) const -> Size {
    return {w - other.w, h - other.h};
  }
  [[nodiscard]] auto operator*(Size other) const -> Size {
    return {w * other.w, h * other.h};
  }
  [[nodiscard]] auto operator/(Size other) const -> Size {
    return {w / other.w, h / other.h};
  }

  [[nodiscard]] auto operator*(T val) const -> Size {
    return {w * val, h * val};
  }
  [[nodiscard]] auto operator/(T val) const -> Size {
    return {w / val, h / val};
  }

  auto operator-() const -> Size { return {w * -1, h * -1}; }

  void operator+=(Size other) {
    w += other.w;
    h += other.h;
  }
  void operator-=(Size other) {
    w -= other.w;
    h -= other.h;
  }
  void operator*=(Size other) {
    w *= other.w;
    h *= other.h;
  }
  void operator/=(Size other) {
    w /= other.w;
    h /= other.h;
  }
  void operator*=(T val) {
    w *= val;
    h *= val;
  }
  void operator/=(T val) {
    w /= val;
    h /= val;
  }
};
