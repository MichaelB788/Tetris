#ifndef DIRECTION_H
#define DIRECTION_H
#include <stdint.h>

/// @brief enum values corresponding to horizontal, vertical, and rotational directions.
struct Direction {
	enum class Rotation : uint8_t { CLOCKWISE, COUNTERCLOCKWISE };
	enum class Horizontal : uint8_t { LEFT, RIGHT };
	enum class Vertical : uint8_t { UP, DOWN };
};

#endif
