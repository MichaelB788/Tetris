#include "core/tetromino-management.hpp"

bool TetrominoManagement::switchToNext(Tetromino& currentTetromino, Tetromino& nextTetromino, Matrix& matrix) {
	currentTetromino = nextTetromino;
	nextTetromino = generateRandomTetromino();

	while (matrix.doesTetrominoCollideGround(currentTetromino)) {
		currentTetromino.shift(Vector2::up());
		if (matrix.isTetrominoOutOfBounds(currentTetromino)) {
			return false;
		}
	}

	matrix.placeTetromino(currentTetromino);
	return true;
}

void TetrominoManagement::swapWithHold(Tetromino& currentTetromino, Tetromino& storedTetromino, Matrix& matrix) {
	matrix.removeTetromino(currentTetromino);

	const Tetromino temp = storedTetromino;
	storedTetromino = currentTetromino;
	currentTetromino = temp;

	matrix.placeTetromino(currentTetromino);
}

Tetromino TetrominoManagement::generateRandomTetromino() {
	return Tetromino({Matrix::TETROMINO_INITIAL_POS});
}

Tetromino TetrominoManagement::generateNullTetromino() {
	return Tetromino(TetrominoType::NONE, {Matrix::TETROMINO_INITIAL_POS});
};
