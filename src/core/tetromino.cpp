#include "core/tetromino.hpp"

Tetromino::Tetromino() : m_pivot({0, 0}) {
	m_type = getRandomType(); 
	m_coordinates = generateShape(m_type, m_pivot);
};

Tetromino::Tetromino(TetrominoType type)
	: m_pivot({0, 0}),
		m_type(type)
{
	m_coordinates = generateShape(m_type, m_pivot);
};

Tetromino::Tetromino(Vector2 initialPos) : m_pivot(initialPos) {
	m_type = getRandomType(); 
	m_coordinates = generateShape(m_type, m_pivot);
};

Tetromino::Tetromino(TetrominoType type, Vector2 initialPos)
	: m_type(type), 
		m_pivot(initialPos)
{
	m_coordinates = generateShape(m_type, m_pivot);
};

void Tetromino::shift(int dx, int dy) {
	const Vector2 translation{dx, dy}; 
	m_pivot + translation;
	for (auto& vec : m_coordinates) vec + translation;
}

void Tetromino::shift(const Vector2& translation) {
	m_pivot + translation;
	for (auto& vec : m_coordinates) vec + translation;
}

void Tetromino::rotateClockwise() {
	if (m_type != TetrominoType::O) {
		for (auto &vec : m_coordinates) {
			vec.rotate90Degrees(true, m_pivot);
		}
	}
}

void Tetromino::rotateCounterclockwise() {
	if (m_type != TetrominoType::O) {
		for (auto &vec : m_coordinates) {
			vec.rotate90Degrees(false, m_pivot);
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
				pivot + Vector2::left() + Vector2::left(),
				pivot + Vector2::left(),
				pivot,
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
				pivot + Vector2::left(),
				pivot,
				pivot + Vector2::right(),
				pivot + Vector2::up()
			};
		case TetrominoType::Z:
			return {
				pivot + Vector2::up() + Vector2::left(),
				pivot + Vector2::up(),
				pivot,
				pivot + Vector2::right(),
			};
		case TetrominoType::S:
			return {
				pivot + Vector2::left(),
				pivot,
				pivot + Vector2::right(),
				pivot + Vector2::up() + Vector2::right()
			};
		case TetrominoType::J:
			return {
				pivot + Vector2::up() + Vector2::left(),
				pivot + Vector2::up(),
				pivot,
				pivot + Vector2::right(),
			};
		case TetrominoType::L:
			return {
				pivot + Vector2::left(),
				pivot,
				pivot + Vector2::right(),
				pivot + Vector2::up() + Vector2::right()
			};
		default:
			return {
				pivot, pivot, pivot, pivot
			};
	}
}
