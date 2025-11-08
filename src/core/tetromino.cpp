#include "core/tetromino.hpp"

Tetromino::Tetromino(Vector2 initialPos) {
	m_type = getRandomType(); 
	m_coordinates = generateShape(m_type, initialPos);
};

Tetromino::Tetromino(TetrominoType type, Vector2 initialPos) : m_type(type) {
	m_coordinates = generateShape(m_type, initialPos);
};

void Tetromino::operator=(const Tetromino& other) {
	m_coordinates = other.m_coordinates;
	m_type = other.m_type;
}

void Tetromino::shift(const Vector2& translation) {
	for (auto& vec : m_coordinates) vec += translation;
}

void Tetromino::rotate(Vector2::Rotation rotation) {
	if (m_type != TetrominoType::O) {
		for (int i = 1; i < 4; i++) {
			Vector2::rotate90Degrees(rotation, m_coordinates[i], m_coordinates[0]);
		}
	}
}

TetrominoType Tetromino::getRandomType() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 6);
	return TetrominoType(distrib(gen));
}

std::array<Vector2, 4> Tetromino::generateShape(TetrominoType& type, Vector2& pivot) {
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
		default:
			return {
				pivot, pivot, pivot, pivot
			};
	}
}
