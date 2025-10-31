#ifndef VECTOR2_H
#define VECTOR2_H

/// @brief Stores two (x, y) coordinates.
struct Vector2 {
	int x{};
	int y{};

	constexpr Vector2() = default;
	constexpr Vector2(int x, int y) : x(x), y(y) {}

	inline void translate(int dx, int dy) {
		x += dx;
		y += dy;
	}

	void rotate90Degrees(bool clockwise, const Vector2& pivot);

	inline constexpr Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

	inline constexpr Vector2 operator-(const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	}

	inline constexpr bool operator==(const Vector2& other) const {
		return x == other.x && y == other.y;
	}

	/// @brief Shorthand for Vector2(0, -1)
	static const Vector2 up;

	/// @brief Shorthand for Vector2(0, 1)
	static const Vector2 down;

	/// @brief Shorthand for Vector2(-1, 0)
	static const Vector2 left;

	/// @brief Shorthand for Vector2(1, 0)
	static const Vector2 right;

	/// @brief Shorthand for Vector2(0, 0)
	static const Vector2 zero;

	/// @brief Shorthand for Vector2(1, 1)
	static const Vector2 one;
};

#endif
