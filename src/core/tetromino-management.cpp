#include "core/tetromino-management.hpp"

bool TetrominoManagement::switchToNext(Tetromino& current, Tetromino& next, Matrix& matrix) {
	current = next;
	next = generateRandomTetromino();

	while (matrix.doesTetrominoCollideGround(current)) {
		current.shift(Vector2::up());
		if (matrix.isTetrominoOutOfBounds(current)) return false;
	}

	matrix.placeTetromino(current);
	return true;
}

bool TetrominoManagement::swapWithHold(Tetromino& current, Tetromino& stored, Matrix& matrix) {
	matrix.removeTetromino(current);

	current.move(Matrix::TETROMINO_INITIAL_POS);
	std::swap(current, stored);

	while (matrix.doesTetrominoCollideGround(current)) {
		current.shift(Vector2::up());
		if (matrix.isTetrominoOutOfBounds(current)) return false;
	}

	matrix.placeTetromino(current);
	return true;
}

Tetromino TetrominoManagement::generateRandomTetromino() {
	return Tetromino({ Matrix::TETROMINO_INITIAL_POS });
}

Tetromino TetrominoManagement::generateNullTetromino() {
	return Tetromino(TetrominoType::NONE, { Matrix::TETROMINO_INITIAL_POS });
}
