#ifndef TETROMINO_GENERATOR_H
#define TETROMINO_GENERATOR_H
#include <array>
#include <random>
#include "core/tetromino-type.hpp"
#include "util/vector2.hpp"

namespace TetrominoGenerator {
	TetrominoType getRandomType();
	const std::array<Vector2, 4> generateShape(TetrominoType type, Vector2 pivot);
}

#endif
