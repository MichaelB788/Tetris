#include "core/tetromino.hpp"

Tetromino::Tetromino(Vector2 initialPos) : type(TetrominoGenerator::getRandomType()) { 
	blocks = TetrominoGenerator::generateShape(type, initialPos);
};

Tetromino::Tetromino(TetrominoType type, Vector2 initialPos) : type(type) {
	blocks = TetrominoGenerator::generateShape(type, initialPos);
};

void Tetromino::shift(Vector2 translation) {
	for (auto& vec : blocks) {
		vec += translation;
	}
}

void Tetromino::shift(int dx, int dy) {
	for (auto& vec : blocks) {
		vec.x += dx;
		vec.y += dy;
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
