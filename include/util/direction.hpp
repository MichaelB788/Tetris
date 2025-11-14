#ifndef DIRECTION_H
#define DIRECTION_H
#include <stdint.h>

/// @brief enum values corresponding to horizontal, vertical, and rotational directions.
namespace Direction {
	enum class Rotation : uint8_t { CLOCKWISE, COUNTERCLOCKWISE };
	enum class Horizontal : uint8_t { LEFT, RIGHT };
	enum class Vertical : uint8_t { UP, DOWN };

	constexpr Rotation getCounterRotation(Rotation rotation) {
		return rotation == Rotation::CLOCKWISE ? Rotation::COUNTERCLOCKWISE : Rotation::CLOCKWISE;
	}

	constexpr Horizontal getOppositeHorizontal(Horizontal direction) {
		return direction == Horizontal::LEFT ? Horizontal::RIGHT : Horizontal::LEFT;
	}
};

#endif
