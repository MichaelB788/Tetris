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

void GameState::moveActorLeft() {
	m_matrix.removeActor(m_currentTetromino);
	m_currentTetromino.shift(Vector2::left());

	if (m_matrix.actorCollidesWall(m_currentTetromino)) {
		m_currentTetromino.shift(Vector2::right());
	}

	m_matrix.placeActor(m_currentTetromino);
}

void GameState::moveActorRight() {
	m_matrix.removeActor(m_currentTetromino);
	m_currentTetromino.shift(Vector2::right());

	if (m_matrix.actorCollidesWall(m_currentTetromino)) {
		m_currentTetromino.shift(Vector2::left());
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

void GameState::rotateActorClockwise() {
	m_matrix.removeActor(m_currentTetromino);
	m_currentTetromino.rotateClockwise();

	if (m_matrix.actorCollidesWall(m_currentTetromino)) {
		m_currentTetromino.rotateCounterclockwise();
	}

	m_matrix.placeActor(m_currentTetromino);
}

void GameState::rotateActorCounterclockwise() {
	m_matrix.removeActor(m_currentTetromino);
	m_currentTetromino.rotateCounterclockwise();

	if (m_matrix.actorCollidesWall(m_currentTetromino)) {
		m_currentTetromino.rotateClockwise();
	}

	m_matrix.placeActor(m_currentTetromino);
}
