#include "core/tetromino-movement.hpp"

void TetrominoMovement::moveTetromino(Tetromino& current, Matrix& matrix, Direction::Horizontal direction) {
	matrix.removeTetromino(current);
	current.shift(Vector2::getHorizontal(direction));

	if (matrix.doesTetrominoCollideImpermeable(current)) {
		current.shift(-Vector2::getHorizontal(direction));
	}

	matrix.placeTetromino(current);
}

bool TetrominoMovement::moveTetrominoDown(Tetromino& current, Matrix& matrix) {
	matrix.removeTetromino(current);
	current.shift(Vector2::down());

	if (matrix.doesTetrominoCollideGround(current)) {
		current.shift(Vector2::up());
		matrix.lockDownTetromino(current);
		return false;
	}
	else {
		matrix.placeTetromino(current);
	}

	return true;
}

void TetrominoMovement::dropTetromino(Tetromino& current, Matrix& matrix) {
	matrix.removeTetromino(current);
	while (!matrix.doesTetrominoCollideGround(current)) {
		current.shift(Vector2::down());
	}
	current.shift(Vector2::up());
	matrix.lockDownTetromino(current);
}
