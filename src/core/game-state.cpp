#include "core/game-state.hpp"

void GameState::gameOver() {
	matrix.clearMatrix();
	tetrominoQueue.reset();
	current = Tetromino(Tetromino::getRandomType(gen), Matrix::TETROMINO_INITIAL_POS);
}

void GameState::moveDown() {
	bool hasMoved = TetrominoMovement::moveTetrominoDown(current, matrix);
	if ( !hasMoved ) spawnNext();
}

void GameState::spawnNext() {
	tetrominoQueue.switchToNext(current);
	current.move(Matrix::TETROMINO_INITIAL_POS);
	while ( matrix.doesTetrominoCollideGround(current) ) {
		current.shift(Vector2::up());
		if ( matrix.isTetrominoOutOfBounds(current) ) {
			gameOver();
			return;
		}
	}
	linesCleared += matrix.clearAndDropLines();
}
