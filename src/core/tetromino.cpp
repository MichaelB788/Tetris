#include "core/tetromino.hpp"

// TODO: Implement SRS and expand these function
void Tetromino::rotateClockwise() {
	if (m_type != TetrominoType::O) {
		Shape::rotateClockwise();
	}
}

// TODO: Implement SRS and expand this function
void Tetromino::rotateCounterclockwise() {
	if (m_type != TetrominoType::O) {
		Shape::rotateCounterclockwise();
	}
}

TetrominoType Tetromino::getRandomType() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 6);
	return TetrominoType(distrib(gen));
}
