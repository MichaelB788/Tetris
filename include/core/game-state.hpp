#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

class GameState {
public:
	GameState();
	void changeActor();

private:
	static constexpr unsigned int INIT_X = 5, INIT_Y = 5;
	Matrix m_scene;
	Tetromino m_current{{INIT_X, INIT_Y}};
	Tetromino m_next{{INIT_X, INIT_Y}};
};

#endif
