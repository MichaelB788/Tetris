#include "core/game-state.hpp"

GameState::GameState() : m_actor(Tetromino({INIT_X, INIT_Y})) {
	m_scene.assignActor(&m_actor);
}

void GameState::changeActor() {
	m_actor = Tetromino({INIT_X, INIT_Y});
}
