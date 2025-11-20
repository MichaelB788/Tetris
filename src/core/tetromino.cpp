#include "core/tetromino.hpp"
#include <random>

void Tetromino::operator=(const Tetromino& other) {
	type = other.type;
	blocks = other.blocks;
	rotationState = other.rotationState;
}

Tetromino::Type Tetromino::getRandomType(std::mt19937& gen) {
	static constexpr std::array<Tetromino::Type, 7> types { Type::I, Type::O, Type::T, Type::Z, Type::S, Type::J, Type::L };

	static std::uniform_int_distribution<> distrib(0, types.size() - 1);
	return types[distrib(gen)];
}

void Tetromino::shift(int dx, int dy) {
	for (auto& block : blocks) {
		block.x += dx;
		block.y += dy;
	}
}

void Tetromino::move(int x, int y) {
	int dx = x - blocks[0].x;
	int dy = y - blocks[0].y;

	for (auto& block : blocks) {
		block.x += dx;
		block.y += dy;
	}
}

void Tetromino::rotate(Direction::Rotation direction) {
	if (type != Tetromino::Type::O) {
		for (int i = 1; i < 4; i++) {
			blocks[i].rotate90Degrees(direction, blocks[0]);
		}
		updateRotationState(direction);
	}
}

void Tetromino::updateRotationState(Direction::Rotation direction) {
	if ( direction == Direction::Rotation::CLOCKWISE ) {
		rotationState = (rotationState + 1) % 4;
	} else {
		rotationState = (rotationState - 1 < 0) ? 3 : rotationState - 1;
	}
}
