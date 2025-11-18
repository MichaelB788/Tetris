#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <ostream>
#include <stdint.h>
#include "direction.hpp"

/// @brief A Vector2 consisting of integer values.
struct Vector2 {
	int x, y;

	/// @brief Instantiates this Vector2 as (x, y)
	constexpr Vector2(int x, int y) : x(x), y(y) {}

	/// @brief Instantiates this Vector2 as (0, 0)
	constexpr Vector2() : x(0), y(0) {}

	Vector2 operator+(const Vector2& other) const {
		return {x + other.x, y + other.y};
	}

	Vector2 operator-(const Vector2& other) const {
		return {x - other.x, y - other.y};
	}

	Vector2 operator*(const Vector2& other) const {
		return {x * other.x, y * other.y};
	}

	Vector2 operator/(const Vector2& other) const {
		return {x / other.x, y / other.y};
	}

	Vector2 operator+(const int other) const {
		return {x + other, y + other};
	}

	Vector2 operator-(const int other) const {
		return {x - other, y - other};
	}

	Vector2 operator*(const int other) const {
		return {x * other, y * other};
	}

	Vector2 operator/(const int other) const {
		return {x / other, y / other};
	}

	void operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
	}

	bool operator==(const Vector2& other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2& other) const {
		return x != other.x && y != other.y;
	}

	/// @return Negation of this Vector2
	Vector2 operator-() const {
		return {x * -1, y * -1};
	}

	/// @brief Converts the object data to readable string format. Used for debugging.
	friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
	}

	/* *
	 * @brief Translates this Vector2's original position, (x, y), to one of the following:
	 * - (y, -x), given `Direction::Rotation::CLOCKWISE`
	 * - (-y, x), given `Direction::Rotation::COUNTERCLOCKWISE`
	 */
	void rotate90Degrees(Direction::Rotation rotation, const Vector2& pivot);

	static constexpr Vector2 getVertical(Direction::Vertical vertical) {
		return vertical == Direction::Vertical::UP ? Vector2::up() : Vector2::down();
	}

	static constexpr Vector2 getHorizontal(Direction::Horizontal vertical) {
		return vertical == Direction::Horizontal::LEFT ? Vector2::left() : Vector2::right();
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

struct Dimension2D {
	int w, h;

	constexpr Dimension2D(int w, int h) : w(w), h(h) {}
};

#endif
