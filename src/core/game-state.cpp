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

		if (storedTetromino.getType() == TetrominoType::NONE) {
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

void GameState::moveActor(Vector2::Horizontal direction) {
	matrix.removeActor(currentTetromino);
	Vector2 translation = direction == Vector2::Horizontal::LEFT
		? Vector2::left()
		: Vector2::right();
	currentTetromino.shift(translation);

	if (matrix.doesActorCollideImpermeable(currentTetromino)) {
		currentTetromino.shift(-translation);
	}
}

void GameState::moveActorDown() {
	matrix.removeActor(currentTetromino);
	currentTetromino.shift(Vector2::down());

	if (matrix.doesActorCollideGround(currentTetromino)) {
		currentTetromino.shift(Vector2::up());
		matrix.lockDownActor(currentTetromino);
		switchToNextTetromino();
	}
}

void GameState::dropActor() {
	matrix.removeActor(currentTetromino);
	currentTetromino = matrix.calculateDropPosition(currentTetromino);
	matrix.lockDownActor(currentTetromino);
	switchToNextTetromino();
}

void GameState::rotateActor(Vector2::Rotation rotationDirection) {
	matrix.removeActor(currentTetromino);
	currentTetromino.rotate(rotationDirection);
	if (matrix.doesActorCollideImpermeable(currentTetromino)) {
		currentTetromino.shift(wallKickTranslation());
		if (matrix.doesActorCollideImpermeable(currentTetromino)) {
			currentTetromino.shift(-wallKickTranslation());
			performSRSTests();
		}
	}
}

Vector2 GameState::wallKickTranslation() const {
	return currentTetromino.center().x > Matrix::WIDTH / 2
		? Vector2::left()
		: Vector2::right();
}

void GameState::resetTetromino() {
	currentTetromino = generateRandomTetromino();
	nextTetromino = generateRandomTetromino();
	storedTetromino = generateNullTetromino();
}

void GameState::performSRSTests() {
	const Tetromino temp = currentTetromino;
	int tries = 0;
	for (const auto& offset : SRS::offset_data(currentTetromino)) {
		currentTetromino.shift(offset);
		if (matrix.doesActorCollideImpermeable(currentTetromino)) {
			currentTetromino.shift(-offset);
			++tries;
		} else {
			break;
		}
	}
	if (tries == 5) {
		currentTetromino = temp;
	}
}
