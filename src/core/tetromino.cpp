#include "core/tetromino.hpp"

TetrominoType Tetromino::typeGenerator() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 6);
  return TetrominoType(distrib(gen));
}

Tetromino::Tetromino(TetrominoType type, Vector2 pivot) : m_type(type) {
	switch(type) {
		case TetrominoType::I:
			m_coordinates = {
				pivot,
				Vector2(pivot.x + 2, pivot.y),
				Vector2(pivot.x + 1, pivot.y),
				Vector2(pivot.x - 1, pivot.y)
			};
			break;
		case TetrominoType::O:
			m_coordinates = {
				pivot,
				Vector2(pivot.x + 1, pivot.y),
				Vector2(pivot.x, pivot.y + 1),
				Vector2(pivot.x + 1, pivot.y + 1)
			};
			break;
		case TetrominoType::T:
			m_coordinates = {
				pivot,
				Vector2(pivot.x - 1, pivot.y),
				Vector2(pivot.x, pivot.y + 1),
				Vector2(pivot.x, pivot.y + 1)
			};
			break;
		case TetrominoType::Z:
			m_coordinates = {
				pivot,
				Vector2(pivot.x - 1, pivot.y - 1),
				Vector2(pivot.x, pivot.y - 1),
				Vector2(pivot.x + 1, pivot.y)
			};
			break;
		case TetrominoType::S:
			m_coordinates = {
				pivot,
				Vector2(pivot.x - 1, pivot.y),
				Vector2(pivot.x, pivot.y - 1),
				Vector2(pivot.x + 1, pivot.y - 1)
			};
			break;
		case TetrominoType::J:
			m_coordinates = {
				pivot,
				Vector2(pivot.x - 1, pivot.y - 1),
				Vector2(pivot.x - 1, pivot.y),
				Vector2(pivot.x + 1, pivot.y)
			};
			break;
		case TetrominoType::L:
			m_coordinates = {
				pivot,
				Vector2(pivot.x - 1, pivot.y),
				Vector2(pivot.x + 1, pivot.y),
				Vector2(pivot.x + 1, pivot.y + 1)
			};
			break;
		default:
			break;
	}
}

void Tetromino::rotate(bool clockwise) {
	if (m_type != TetrominoType::O) {
		constexpr unsigned int PIVOT = 0;
		Vector2& pivot = m_coordinates[PIVOT];
		for (auto &vec : m_coordinates) {
			Vector2 translation = vec - m_coordinates[PIVOT];
			Vector2 rotated = clockwise ?
				Vector2(translation.y, -translation.x) : Vector2(-translation.y, translation.x);
			vec.x = m_coordinates[PIVOT].x + rotated.x;
			vec.y = m_coordinates[PIVOT].x + rotated.y;
		}
	}
}

void Tetromino::move(int dx, int dy) {
	for (auto& vec : m_coordinates) {
		vec.x += dx;
		vec.y += dx;
	}
}
