#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

class GameState {
public:
	GameState();

private:
	void changeActor();

private:
	static constexpr unsigned int INIT_X = 5, INIT_Y = 5;
	Matrix m_scene;
	Tetromino m_actor;
};

#endif
