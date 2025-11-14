#include "core/game-state.hpp"
#include "core/tetromino-management.hpp"

void GameState::gameOver() {
	matrix.clearMatrix();
	currentTetromino = TetrominoManagement::generateRandomTetromino();
	nextTetromino = TetrominoManagement::generateRandomTetromino();
	storedTetromino = TetrominoManagement::generateNullTetromino();
	swapUsedThisTurn = false;
}

void GameState::moveDown() {
	bool hasMoved = TetrominoMovement::moveTetrominoDown(currentTetromino, matrix);
	if ( hasMoved ) return;
	else spawnNext();
}

void GameState::drop() {
	TetrominoMovement::dropTetromino(currentTetromino, matrix);
	spawnNext();
}

void GameState::swap() {
	if ( !swapUsedThisTurn ) {
		swapUsedThisTurn = true;
		bool isFirstSwap = storedTetromino.getType() == TetrominoType::NONE;

		TetrominoManagement::swapWithHold(currentTetromino, storedTetromino, matrix);
		if ( isFirstSwap ) spawnNext(); 
	}
}

void GameState::spawnNext() {
	bool canPlaceNext = TetrominoManagement::switchToNext(currentTetromino, nextTetromino, matrix);
	if ( !canPlaceNext ) {
		gameOver();
	} else {
		linesCleared += matrix.clearAndDropLines();
		swapUsedThisTurn = false;
	}
}
