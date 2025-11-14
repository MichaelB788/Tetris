#include "core/tetromino.hpp"

namespace TetrominoInitializer {
	TetrominoType getRandomType() {
		using Type = TetrominoType;
		std::array<TetrominoType, 7> types { Type::I, Type::O, Type::J, Type::L, Type::S, Type::Z, Type::T };

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(0, types.size() - 1);

		return types[distrib(gen)];
	}

	const std::array<Vector2, 4> generateShape(TetrominoType type, Vector2 pivot) {
		switch(type) {
			case TetrominoType::I:
				return {
					pivot,
					pivot + Vector2::left(),
					pivot + Vector2::right(),
					pivot + Vector2::right() + Vector2::right()
				};
			case TetrominoType::O:
				return {
					pivot,
					pivot + Vector2::right(),
					pivot + Vector2::down(),
					pivot + Vector2::down() + Vector2::right()
				};
			case TetrominoType::T:
				return {
					pivot,
					pivot + Vector2::left(),
					pivot + Vector2::right(),
					pivot + Vector2::up()
				};
			case TetrominoType::Z:
				return {
					pivot,
					pivot + Vector2::up() + Vector2::left(),
					pivot + Vector2::up(),
					pivot + Vector2::right(),
				};
			case TetrominoType::S:
				return {
					pivot,
					pivot + Vector2::left(),
					pivot + Vector2::up(),
					pivot + Vector2::up() + Vector2::right()
				};
			case TetrominoType::J:
				return {
					pivot,
					pivot + Vector2::up() + Vector2::left(),
					pivot + Vector2::left(),
					pivot + Vector2::right(),
				};
			case TetrominoType::L:
				return {
					pivot,
					pivot + Vector2::up() + Vector2::right(),
					pivot + Vector2::right(),
					pivot + Vector2::left()
				};
			case TetrominoType::NONE: default:
				return {
					pivot, pivot, pivot, pivot
				};
		}
	}
}

Tetromino::Tetromino(Vector2 initialPos) : type(TetrominoInitializer::getRandomType()) { 
	blocks = TetrominoInitializer::generateShape(type, initialPos);
};

Tetromino::Tetromino(TetrominoType type, Vector2 initialPos) : type(type) {
	blocks = TetrominoInitializer::generateShape(type, initialPos);
};

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
	for (int i = 1; i < 4; i++) {
		blocks[i].rotate90Degrees(direction, blocks[0]);
	}
	updateRotationState(direction);
}

void Tetromino::updateRotationState(Direction::Rotation direction) {
	if ( direction == Direction::Rotation::CLOCKWISE ) {
		rotationState = (rotationState + 1) % 4;
	} else {
		rotationState = (rotationState - 1 < 0) ? 3 : rotationState - 1;
	}
}
