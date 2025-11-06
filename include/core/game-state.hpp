#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

// TODO: Implement game overs

class GameState {
public:
	GameState();
	void update();

	void switchToNextTetromino();
	void swapActorWithStored();

	void moveActorLeft();
	void moveActorRight();
	void moveActorDown();

private:
	static constexpr unsigned int INIT_X = 5, INIT_Y = 5;

	Matrix m_scene;
	
	bool isSwapped = false;
	Tetromino m_currentTetromino{{INIT_X, INIT_Y}};
	Tetromino m_nextTetromino{{INIT_X, INIT_Y}};
	Tetromino m_storedTetromino{TetrominoType::NONE, {INIT_X, INIT_Y}};
};

#endif
