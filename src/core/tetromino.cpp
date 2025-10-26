#include "core/tetromino.hpp"

Tetromino::Tetromino(TetrominoType type, Vector2 pivot) : m_type(type) {
	Vector2 v1, v2, v3;

	switch(type) {
		case TetrominoType::I:
			v1 = pivot.rightCell().rightCell();
			v2 = pivot.rightCell();
			v3 = pivot.leftCell();
			break;
		case TetrominoType::O:
			v1 = pivot.rightCell();
			v2 = pivot.bottomCell();
			v3 = pivot.bottomCell().rightCell();
			break;
		case TetrominoType::T:
			v1 = pivot.leftCell();
			v2 = pivot.rightCell();
			v3 = pivot.topCell();
			break;
		case TetrominoType::Z:
			v1 = pivot.topCell().leftCell();
			v2 = pivot.topCell();
			v3 = pivot.rightCell();
			break;
		case TetrominoType::S:
			v1 = pivot.leftCell();
			v2 = pivot.topCell();
			v3 = pivot.topCell().rightCell();
			break;
		case TetrominoType::J:
			v1 = pivot.topCell().leftCell();
			v2 = pivot.leftCell();
			v3 = pivot.rightCell();
			break;
		case TetrominoType::L:
			v1 = pivot.leftCell();
			v2 = pivot.rightCell();
			v3 = pivot.topCell().rightCell();
			break;
		default:
			break;
	}

	m_coordinates = { pivot, v1, v2, v3 };
}

void Tetromino::rotateClockwise() {
	if (m_type != TetrominoType::O) {
		constexpr unsigned int PIVOT_INDEX = 0;
		Vector2 pivot = m_coordinates[PIVOT_INDEX];

		for (auto &c : m_coordinates) {
			int dx = c.x - pivot.x;
			int dy = c.y - pivot.y;
			int rotated_x = -dy;
			int rotated_y = dx;
			c.x = pivot.x + rotated_x;
			c.y = pivot.y + rotated_y;
		}
	}
}

void Tetromino::rotateCounterclockwise() {
	if (m_type != TetrominoType::O) {
		constexpr unsigned int PIVOT_INDEX = 0;
		Vector2 pivot = m_coordinates[PIVOT_INDEX];

		for (auto &c : m_coordinates) {
			int dx = c.x - pivot.x;
			int dy = c.y - pivot.y;
			int rotated_x = -dy;
			int rotated_y = dx;
			c.x = pivot.x + rotated_x;
			c.y = pivot.y + rotated_y;
		}
	}
}
