#include "core/game-state.hpp"

void GameState::gameOver() {
	matrix.clearMatrix();
	tetrominoQueue.reset();
	current = Tetromino(Tetromino::getRandomType(gen), Matrix::TETROMINO_INITIAL_POS);
}

void GameState::moveDown() {
	bool hasMoved = TetrominoMovement::moveTetrominoDown(current, matrix);
	if ( !hasMoved ) {
		tetrominoQueue.switchToNext(current);
		spawnNext();
	}
}

void GameState::drop() {
	TetrominoMovement::dropTetromino(current, matrix);
	tetrominoQueue.switchToNext(current);
	spawnNext();
}

void GameState::hold() {
	if ( !tetrominoQueue.isCurrentHeld() ) {
		matrix.removeTetromino(current);
		tetrominoQueue.holdCurrent(current);
		spawnNext();
	}
}

void GameState::spawnNext() {
	current.move(Matrix::TETROMINO_INITIAL_POS);
	matrix.placeTetromino(current);
	linesCleared += matrix.clearAndDropLines();
}
