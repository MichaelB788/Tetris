#ifndef COMPASS_H
#define COMPASS_H
#include "util/direction.hpp"
#include <stdint.h>
#include <array>

/// @brief Tracks which direction the object is facing following a rotation
class Compass {
public:
	enum class Pole : uint8_t {
		NORTH, EAST, SOUTH, WEST
	};

	inline void rotate(Direction::Rotation direction) {
		if (direction == Direction::Rotation::CLOCKWISE) {
			index = (index + 1) % 4;
		} else {
			index = (index - 1 < 0) ? 3 : index - 1;
		}
	}

	inline Pole value() const { return states[index]; }

private:
	std::array<Pole, 4> states = { Pole::NORTH, Pole::EAST, Pole::SOUTH, Pole::WEST };
	int index = 0;
};

#endif
