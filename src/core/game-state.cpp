#include "core/game-state.hpp"
#include "core/tetromino-management.hpp"

void GameState::gameOver() {
	matrix.clearMatrix();
	tetrominoQueue.reset();
	current = Tetromino(Tetromino::getRandomType(gen), Matrix::TETROMINO_INITIAL_POS);
}

void GameState::moveDown() {
	bool hasMoved = TetrominoMovement::moveTetrominoDown(current, matrix);
	if ( hasMoved ) return;
	else spawnNext();
}

void GameState::drop() {
	TetrominoMovement::dropTetromino(current, matrix);
	spawnNext();
}

void GameState::hold() {
	tetrominoQueue.holdCurrent(current);
	current.move(Matrix::TETROMINO_INITIAL_POS);
}

void GameState::spawnNext() {
	while ( matrix.doesTetrominoCollideGround(current) ) {
		current.shift(Vector2::up());
		if ( matrix.isTetrominoOutOfBounds(current) ) {
			gameOver();
			return;
		}
	}

	linesCleared += matrix.clearAndDropLines();
}
