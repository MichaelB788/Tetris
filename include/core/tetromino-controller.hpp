#ifndef TETROMINO_CONTROLLER_H
#define TETROMINO_CONTROLLER_H
#include "util/vector2.hpp"
#include "core/game-state.hpp"
#include "core/super-rotation-system.hpp"

/// @brief Controls the movement of a Tetromino actor within the Matrix. 
class TetrominoController {
public:
	TetrominoController(GameState& state)
		: actor(state.currentTetromino),
			scene(state.matrix)
	{};
	
	void moveActor(Direction::Horizontal direction);
	void moveActorDown();
	void dropActor();
	void rotateActor(Direction::Rotation rotationDirection);

private:
	Tetromino& actor;
	Matrix& scene;
	SuperRotationSystem SRS;
};

#endif
