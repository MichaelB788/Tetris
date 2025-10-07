#ifndef VECTOR2_H
#define VECTOR2_H

/// @brief Stores two (x, y) coordinates.
struct Vector2 {
	int x{};
  int y{};
  constexpr Vector2() = default;
  constexpr Vector2(int x, int y) : x(x), y(y) {};
};

#endif
