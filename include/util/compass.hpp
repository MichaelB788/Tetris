#ifndef COMPASS_H
#define COMPASS_H
#include "util/vector2.hpp"
#include <stdint.h>
#include <array>

/// @brief Tracks which direction the object is facing following a rotation
class Compass {
public:
	enum class Direction : uint8_t {
		NORTH, EAST, SOUTH, WEST
	};

	inline void rotate(Vector2::Rotation direction) {
		if (direction == Vector2::Rotation::CLOCKWISE) {
			index = (index + 1) % 4;
		} else {
			index = (index - 1 < 0) ? 3 : index - 1;
		}
	}

	inline Direction value() const { return states[index]; }

private:
	std::array<Direction, 4> states = { Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST };
	int index = 0;
};

#endif
