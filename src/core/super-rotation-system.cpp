#include "core/super-rotation-system.hpp"

SuperRotationSystem::SuperRotationSystem(Tetromino& tetromino) : m_tetromino(tetromino) {
	using v2 = Vector2;
	if (m_tetromino.type() == TetrominoType::I) {
		m_offsetData = {{
			{ v2(0, 0), v2(0, 0), v2(0, 0), v2(0, 0), v2(0, 0), },
			{ v2(0, 0), v2(0, 0), v2(0, 0), v2(0, 0), v2(0, 0), },
			{ v2(0, 0), v2(0, 0), v2(0, 0), v2(0, 0), v2(0, 0), },
			{ v2(0, 0), v2(0, 0), v2(0, 0), v2(0, 0), v2(0, 0), },
		}};
	}
}
