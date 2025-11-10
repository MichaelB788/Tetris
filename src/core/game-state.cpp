#include "core/game-state.hpp"

void GameState::update() {
	m_matrix.placeActor();
	m_matrix.checkAndClearLines();
	m_matrixRenderer.renderMatrix();
}

void GameState::gameOver() {
	m_matrix.clearMatrix();
}

void GameState::switchToNextTetromino() {
	m_isSwapped = false;
	m_currentTetromino = m_nextTetromino;
	m_currentTetromino = generateRandomTetromino();

	while (m_matrix.actorCollidesGround()) {
		m_currentTetromino.shift(Vector2::up());
		if (m_matrix.tetrominoIsOutOfBounds(m_currentTetromino)) {
			gameOver();
			break;
		}
	}
}

void GameState::swapActorWithStored() {
	if (!m_isSwapped) {
		m_matrix.removeActor();
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
	m_matrix.removeActor();
	Vector2 translation = direction == Vector2::Horizontal::LEFT
		? Vector2::left()
		: Vector2::right();
	m_currentTetromino.shift(translation);

	if (m_matrix.actorCollidesImpermiable()) {
		m_currentTetromino.shift(-translation);
	}
}

void GameState::moveActorDown() {
	m_matrix.removeActor();
	m_currentTetromino.shift(Vector2::down());

	if (m_matrix.actorCollidesGround()) {
		m_currentTetromino.shift(Vector2::up());
		m_matrix.groundActor();
		switchToNextTetromino();
	}
}

void GameState::dropActor() {
	m_matrix.removeActor();
	m_matrix.dropTetromino(m_currentTetromino);
	m_matrix.groundActor();
	switchToNextTetromino();
}

void GameState::rotateActor(Vector2::Rotation rotationDirection) {
	m_matrix.removeActor();
	m_currentTetromino.rotate(rotationDirection);
	if (m_matrix.actorCollidesImpermiable()) {
		m_currentTetromino.shift(wallKickTranslation());
		if (m_matrix.actorCollidesImpermiable()) {
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

void GameState::performSRSTests() {
	const Tetromino temp = m_currentTetromino;
	int tries = 0;
	for (const auto& offset : SRS::offset_data(m_currentTetromino)) {
		m_currentTetromino.shift(offset);
		if (m_matrix.actorCollidesImpermiable()) {
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
