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
	static constexpr Vector2 up() { return {0, -1}; }

	/// @brief Shorthand for Vector2(0, 1)
	static constexpr Vector2 down() { return {0, 1}; }

	/// @brief Shorthand for Vector2(-1, 0)
	static constexpr Vector2 left() { return {-1, 0}; }

	/// @brief Shorthand for Vector2(1, 0)
	static constexpr Vector2 right() { return {1, 0}; }

	/// @brief Shorthand for Vector2(0, 0)
	static constexpr Vector2 zero() { return {0, 0}; }

	/// @brief Shorthand for Vector2(1, 1)
	static constexpr Vector2 one() { return {1, 1}; }
};

#endif
