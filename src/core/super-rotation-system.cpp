#include "core/super-rotation-system.hpp"

SuperRotationSystem::SuperRotationSystem(Tetromino& tetromino) : m_tetromino(tetromino) {
	if (m_tetromino.type() == TetrominoType::I) {
		m_offsetData = {{
			{ Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), },
			{ Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), },
			{ Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), },
			{ Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), },
		}};
	}
}
