#include "core/game-state.hpp"

void GameState::gameOver() {
	matrix.clearMatrix();
	currentTetromino = TetrominoManagement::generateRandomTetromino();
	nextTetromino = TetrominoManagement::generateRandomTetromino();
	storedTetromino = TetrominoManagement::generateNullTetromino();
	currentHasBeenSwapped = false;
}

void GameState::moveDown() {
	if (TetrominoMovement::moveTetrominoDown(currentTetromino, matrix)) return;
	else spawnNextTetromino();
}

void GameState::drop() {
	TetrominoMovement::dropTetromino(currentTetromino, matrix);
	spawnNextTetromino();
}

void GameState::swap() {
	if (!currentHasBeenSwapped) {
		TetrominoManagement::swapWithHold(currentTetromino, storedTetromino, matrix);
		currentHasBeenSwapped = true;

		if (currentTetromino.getType() == TetrominoType::NONE)
			TetrominoManagement::switchToNext(currentTetromino, nextTetromino, matrix);
	}
}

void GameState::spawnNextTetromino() {
	if (!TetrominoManagement::switchToNext(currentTetromino, nextTetromino, matrix)) {
		gameOver();
	} else {
		linesCleared += matrix.clearAndDropLines();
		currentHasBeenSwapped = false;
	}
}
