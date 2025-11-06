#include "core/game-state.hpp"

GameState::GameState()  {
	m_scene.placeActor(m_current);
}

void GameState::changeActor() {
	m_current = Tetromino({INIT_X, INIT_Y});
}
