#ifndef VECTOR2_H
#define VECTOR2_H
#include <ostream>
#include <stdint.h>

/// @brief Stores two (x, y) coordinates.
struct Vector2 {
	int x{};
	int y{};

	enum class Rotation : uint8_t {
		CLOCKWISE,
		COUNTERCLOCKWISE
	};
	enum class Horizontal : uint8_t {
		LEFT,
		RIGHT
	};
	enum class Vertical : uint8_t {
		UP,
		DOWN
	};

	constexpr Vector2() = default;
	constexpr Vector2(int x, int y) : x(x), y(y) {}

	void rotate90Degrees(Rotation rotation, const Vector2& pivot);

	inline Vector2 operator+(const Vector2& other) const {
		return {x + other.x, y + other.y};
	}

	inline Vector2 operator-(const Vector2& other) const {
		return {x - other.x, y - other.y};
	}

	/// @return the negation of the Vector2
	inline constexpr Vector2 operator-() const {
		return {x * -1, y * -1};
	}

	inline void operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
	}

	inline constexpr bool operator==(const Vector2& other) const {
		return x == other.x && y == other.y;
	}

	/// @brief Converts the object data to readable string format. Used for debugging.
	friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
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
