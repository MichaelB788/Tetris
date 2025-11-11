#include "core/super-rotation-system.hpp"

const std::array<Vector2, 5> SRS::offset_data(const Tetromino& tetromino) {
	if (tetromino.getType() == TetrominoType::I) {
		return I_offset_data(tetromino.rotationState());
	} else {
		return standard_offset_data(tetromino.rotationState());
	}
}

const std::array<Vector2, 5> SRS::standard_offset_data(Compass::Direction direction) {
	using v2 = Vector2;
	switch (direction) {
		case Compass::Direction::NORTH:
			return { v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0) };
		case Compass::Direction::EAST:
			return { v2( 0,  0), v2( 1,  0), v2( 1,  1), v2( 0, -2), v2( 1, -2) };
		case Compass::Direction::SOUTH:
			return { v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0) };
		case Compass::Direction::WEST: default:
			return { v2( 0,  0), v2(-1,  0), v2(-1,  1), v2( 0, -2), v2(-1, -2) };
	}
}

const std::array<Vector2, 5> SRS::I_offset_data(Compass::Direction direction) {
	using v2 = Vector2;
	switch (direction) {
		case Compass::Direction::NORTH:
			return { v2( 0,  0), v2(-1,  0), v2( 2,  0), v2(-1,  0), v2( 2,  0), };
		case Compass::Direction::EAST:
			return { v2(-1,  0), v2( 0,  0), v2( 0,  0), v2( 0, -1), v2( 1, +2), };
		case Compass::Direction::SOUTH:
			return { v2(-1, -1), v2( 1, -1), v2(-2, -1), v2( 1,  0), v2(-2,  0), };
		case Compass::Direction::WEST: default:
			return { v2( 0,  1), v2(-1,  0), v2(-1,  1), v2( 0, -2), v2( 0,  0), };
	}
}
