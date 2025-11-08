#include "core/game-state.hpp"

void GameState::update() {
	m_matrix.placeActor(m_currentTetromino);
	if (m_matrix.hasFilledLines()) {
		m_matrix.clearLines();
	}
	m_matrixRenderer.renderMatrix();
}

void GameState::gameOver() {
	m_matrix.clearMatrix();
}

void GameState::switchToNextTetromino() {
	m_isSwapped = false;
	m_currentTetromino = m_nextTetromino;
	m_currentTetromino = generateRandomTetromino();

	while (m_matrix.actorCollidesGround(m_currentTetromino)) {
		m_currentTetromino.shift(Vector2::up());
		if (m_matrix.actorIsOutOfBounds(m_currentTetromino)) {
			gameOver();
			break;
		}
	}
}

void GameState::swapActorWithStored() {
	if (!m_isSwapped) {
		m_matrix.removeActor(m_currentTetromino);
		m_isSwapped = true;

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

	if (m_matrix.actorCollidesImpermiable(m_currentTetromino)) {
		m_currentTetromino.shift(-translation);
	}
}

void GameState::moveActorDown() {
	m_matrix.removeActor(m_currentTetromino);
	m_currentTetromino.shift(Vector2::down());

	if (m_matrix.actorCollidesGround(m_currentTetromino)) {
		m_currentTetromino.shift(Vector2::up());
		m_matrix.groundActor(m_currentTetromino);
		switchToNextTetromino();
	}
}

void GameState::dropActor() {
	m_matrix.removeActor(m_currentTetromino);

	while (!m_matrix.actorCollidesGround(m_currentTetromino)) {
		m_currentTetromino.shift(Vector2::down());
	}
	m_currentTetromino.shift(Vector2::up());
	m_matrix.groundActor(m_currentTetromino);
	switchToNextTetromino();
}

void GameState::rotateActor(Vector2::Rotation rotationDirection) {
	m_matrix.removeActor(m_currentTetromino);
	m_currentTetromino.rotate(rotationDirection);

	while (m_matrix.actorCollidesImpermiable(m_currentTetromino)) {
		Vector2 translation = m_matrix.isActorOnLeft(m_currentTetromino)
			? Vector2::right()
			: Vector2::left();
		m_currentTetromino.shift(translation);
	}
}
