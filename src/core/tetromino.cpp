#include "core/tetromino.hpp"

namespace {
	TetrominoType getRandomType() {
		using Type = TetrominoType;
		std::array<TetrominoType, 7> types { Type::I, Type::O, Type::J, Type::L, Type::S, Type::Z, Type::T };

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(0, types.size() - 1);

		return types[distrib(gen)];
	}

	constexpr std::array<Vector2, 4> generateShape(TetrominoType type, Vector2 pivot) {
		switch(type) {
			case TetrominoType::I:
				return {
					pivot,
					pivot + Vector2::left() + Vector2::left(),
					pivot + Vector2::left(),
					pivot + Vector2::right()
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

Tetromino::Tetromino(Vector2 initialPos) {
	type = getRandomType(); 
	blocks = generateShape(type, initialPos);
};

Tetromino::Tetromino(TetrominoType type, Vector2 initialPos) : type(type) {
	blocks = generateShape(this->type, initialPos);
};

void Tetromino::shift(Vector2 translation) {
	for (auto& vec : blocks) {
		vec += translation;
	}
}

void Tetromino::rotate(Direction::Rotation rotation) {
	for (int i = 1; i < 4; i++) {
		blocks[i].rotate90Degrees(rotation, blocks[0]);
	}
	rotationCompass.rotate(rotation);
}
