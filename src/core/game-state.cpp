#include "core/game-state.hpp"

void GameState::update() {
	m_matrix.placeActor(m_currentTetromino);
	if (m_matrix.hasFilledLines()) {
		m_matrix.clearLines();
	}
	m_matrixRenderer.renderMatrix();
}

void GameState::switchToNextTetromino() {
	isSwapped = false;
	m_currentTetromino = m_nextTetromino;
	m_currentTetromino = Tetromino({INIT_X, INIT_Y});
}

void GameState::swapActorWithStored() {
	if (!isSwapped) {
		isSwapped = true;
		if (m_storedTetromino.type() == TetrominoType::NONE) {
			m_storedTetromino = m_currentTetromino;
			m_currentTetromino = m_nextTetromino;
			m_nextTetromino = Tetromino(Tetromino::getRandomType(), {INIT_X, INIT_Y});
		} else {
			const Tetromino temp = m_storedTetromino;
			m_storedTetromino = m_currentTetromino;
			m_currentTetromino = temp;
		}
	}
}

void GameState::moveActor(Vector2::Horizontal direction) {
	m_matrix.removeActor(m_currentTetromino);
	Vector2 translation = direction == Vector2::Horizontal::LEFT ?
			Vector2::left()
		: Vector2::right();
	m_currentTetromino.shift(translation);

	if (m_matrix.actorCollidesImpermiable(m_currentTetromino)) {
		m_currentTetromino.shift(-translation);
	}

	m_matrix.placeActor(m_currentTetromino);
}

void GameState::moveActorDown() {
	m_matrix.removeActor(m_currentTetromino);
	m_currentTetromino.shift(Vector2::down());

	if (m_matrix.actorCollidesGround(m_currentTetromino)) {
		m_currentTetromino.shift(Vector2::up());
		m_matrix.placeActor(m_currentTetromino);
		m_matrix.groundActor(m_currentTetromino);
		switchToNextTetromino();
	} else {
		m_matrix.placeActor(m_currentTetromino);
	}
}

void GameState::rotateActor(Vector2::Rotation rotationDirection) {
	m_matrix.removeActor(m_currentTetromino);
	m_currentTetromino.rotate(rotationDirection);
	Vector2 translation = rotationDirection == Vector2::Rotation::CLOCKWISE ?
			Vector2::right()
		: Vector2::left();

	m_matrix.placeActor(m_currentTetromino);
}
