#include "core/game-state.hpp"

void GameState::update() {
	m_matrix.placeActor(m_currentTetromino);
	m_matrix.clearAndDropLines();
	m_matrixRenderer.renderMatrixUsingSDL();
}

void GameState::gameOver() {
	m_matrix.clearMatrix();
	resetTetromino();
}

void GameState::switchToNextTetromino() {
	m_currentHasBeenSwapped = false;
	m_currentTetromino = m_nextTetromino;
	m_nextTetromino = generateRandomTetromino();

	while (m_matrix.doesActorCollideGround(m_currentTetromino)) {
		m_currentTetromino.shift(Vector2::up());
		if (m_matrix.isActorOutOfBounds(m_currentTetromino)) {
			gameOver();
			break;
		}
	}
}

void GameState::swapActorWithStored() {
	if (!m_currentHasBeenSwapped) {
		m_matrix.removeActor(m_currentTetromino);
		m_currentHasBeenSwapped = true;

		if (m_storedTetromino.type() == TetrominoType::NONE) {
			m_storedTetromino = m_currentTetromino;
			m_currentTetromino = m_nextTetromino;
			m_nextTetromino = generateRandomTetromino();
		} else {
			const Tetromino temp = m_storedTetromino;
			m_storedTetromino = m_currentTetromino;
			m_currentTetromino = temp;
		}
	}
}

void GameState::moveActor(Vector2::Horizontal direction) {
	m_matrix.removeActor(m_currentTetromino);
	Vector2 translation = direction == Vector2::Horizontal::LEFT
		? Vector2::left()
		: Vector2::right();
	m_currentTetromino.shift(translation);

	if (m_matrix.doesActorCollideImpermeable(m_currentTetromino)) {
		m_currentTetromino.shift(-translation);
	}
}

void GameState::moveActorDown() {
	m_matrix.removeActor(m_currentTetromino);
	m_currentTetromino.shift(Vector2::down());

	if (m_matrix.doesActorCollideGround(m_currentTetromino)) {
		m_currentTetromino.shift(Vector2::up());
		m_matrix.lockDownActor(m_currentTetromino);
		switchToNextTetromino();
	}
}

void GameState::dropActor() {
	m_matrix.removeActor(m_currentTetromino);
	m_currentTetromino = m_matrix.calculateDropPosition(m_currentTetromino);
	m_matrix.lockDownActor(m_currentTetromino);
	switchToNextTetromino();
}

void GameState::rotateActor(Vector2::Rotation rotationDirection) {
	m_matrix.removeActor(m_currentTetromino);
	m_currentTetromino.rotate(rotationDirection);
	if (m_matrix.doesActorCollideImpermeable(m_currentTetromino)) {
		m_currentTetromino.shift(wallKickTranslation());
		if (m_matrix.doesActorCollideImpermeable(m_currentTetromino)) {
			m_currentTetromino.shift(-wallKickTranslation());
			performSRSTests();
		}
	}
}

Vector2 GameState::wallKickTranslation() const {
	return m_currentTetromino.center().x > Matrix::WIDTH / 2
		? Vector2::left()
		: Vector2::right();
}

void GameState::resetTetromino() {
	m_currentTetromino = generateRandomTetromino();
	m_nextTetromino = generateRandomTetromino();
	m_storedTetromino = generateNullTetromino();
}

void GameState::performSRSTests() {
	const Tetromino temp = m_currentTetromino;
	int tries = 0;
	for (const auto& offset : SRS::offset_data(m_currentTetromino)) {
		m_currentTetromino.shift(offset);
		if (m_matrix.doesActorCollideImpermeable(m_currentTetromino)) {
			m_currentTetromino.shift(-offset);
			++tries;
		} else {
			break;
		}
	}
	if (tries == 5) {
		m_currentTetromino = temp;
	}
}
