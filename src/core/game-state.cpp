#include "core/game-state.hpp"

GameState::GameState(Renderer& renderer) : m_matrixRenderer(m_scene, renderer) {
	m_scene.placeActor(m_currentTetromino);
}

void GameState::update() {
	m_scene.placeActor(m_currentTetromino);
	if (m_scene.hasClearedLines()) {
		m_scene.clearLines();
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
	m_scene.removeActor(m_currentTetromino);
	m_currentTetromino.shift(Vector2::left());

	if (m_scene.actorCollidesWall(m_currentTetromino)) {
		m_currentTetromino.shift(Vector2::right());
	} else {
		m_scene.placeActor(m_currentTetromino);
	}
}

void GameState::moveActorRight() {
	m_scene.removeActor(m_currentTetromino);
	m_currentTetromino.shift(Vector2::right());

	if (m_scene.actorCollidesWall(m_currentTetromino)) {
		m_currentTetromino.shift(Vector2::left());
	} else {
		m_scene.placeActor(m_currentTetromino);
	}
}

void GameState::moveActorDown() {
	m_scene.removeActor(m_currentTetromino);
	m_currentTetromino.shift(Vector2::down());

	if (m_scene.actorCollidesGround(m_currentTetromino)) {
		m_currentTetromino.shift(Vector2::up());
		m_scene.placeActor(m_currentTetromino);
		m_scene.groundActor(m_currentTetromino);
		switchToNextTetromino();
	} else {
		m_scene.placeActor(m_currentTetromino);
	}
}
