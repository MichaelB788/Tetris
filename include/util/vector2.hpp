#ifndef VECTOR2_H
#define VECTOR2_H

/// @brief Stores two (x, y) coordinates.
struct Vector2 {
	int x{};
  int y{};
  constexpr Vector2() = default;
  constexpr Vector2(int x, int y) : x(x), y(y) {};

  inline Vector2 topCell()    { return Vector2( x, y-1 ); }
  inline Vector2 rightCell()  { return Vector2( x+1, y ); }
  inline Vector2 bottomCell() { return Vector2( x, y+1 ); }
  inline Vector2 leftCell()   { return Vector2( x-1, y ); }
};

#endif
