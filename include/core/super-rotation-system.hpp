#ifndef SUPER_ROTATION_SYSTEM_H
#define SUPER_ROTATION_SYSTEM_H
#include "util/vector2.hpp"
#include "core/tetromino.hpp"
#include "util/compass.hpp"
#include <array>

namespace SRS {
	const std::array<Vector2, 5> offset_data(const Tetromino& tetromino);
};

#endif
