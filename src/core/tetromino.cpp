#include "core/tetromino.hpp"

void Tetromino::rotateClockwise() {
	if (m_shape.type() != TetrominoType::O) {
		m_shape.rotate90Degrees(true);
	}
}

void Tetromino::rotateCounterclockwise() {
	if (m_shape.type() != TetrominoType::O) {
		m_shape.rotate90Degrees(false);
	}
}

TetrominoType Tetromino::generateRandomType() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 6);
  return TetrominoType(distrib(gen));
}
