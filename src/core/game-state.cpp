#include "core/game-state.hpp"

void GameState::update() {
	matrix.placeActor(currentTetromino);
	matrix.clearAndDropLines();
}

void GameState::gameOver() {
	matrix.clearMatrix();
	resetTetromino();
}

void GameState::switchToNextTetromino() {
	currentHasBeenSwapped = false;
	currentTetromino = nextTetromino;
	nextTetromino = generateRandomTetromino();

	while (matrix.doesActorCollideGround(currentTetromino)) {
		currentTetromino.shift(Vector2::up());
		if (matrix.isActorOutOfBounds(currentTetromino)) {
			gameOver();
			break;
		}
	}
}

void GameState::swapActorWithStored() {
	if (!currentHasBeenSwapped) {
		matrix.removeActor(currentTetromino);
		currentHasBeenSwapped = true;

		if (storedTetromino.type() == TetrominoType::NONE) {
			storedTetromino = currentTetromino;
			currentTetromino = nextTetromino;
			nextTetromino = generateRandomTetromino();
		} else {
			const Tetromino temp = storedTetromino;
			storedTetromino = currentTetromino;
			currentTetromino = temp;
		}
	}
}

void GameState::resetTetromino() {
	currentTetromino = generateRandomTetromino();
	nextTetromino = generateRandomTetromino();
	storedTetromino = generateNullTetromino();
}
