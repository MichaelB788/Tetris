#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "core/matrix.hpp"
#include "core/tetromino-management.hpp"
#include "core/tetromino.hpp"
#include "core/tetromino-movement.hpp"
#include "core/super-rotation-system.hpp"

class GameState {
public:
	GameState()
		: currentTetromino(TetrominoManagement::generateRandomTetromino()),
			ghostTetromino(currentTetromino),
			nextTetromino(TetrominoManagement::generateRandomTetromino()),
			storedTetromino(TetrominoManagement::generateNullTetromino())
	{}

	void moveLeft() {
		TetrominoMovement::moveTetromino(currentTetromino, matrix, Direction::Horizontal::LEFT);
	}

	void moveRight() {
		TetrominoMovement::moveTetromino(currentTetromino, matrix, Direction::Horizontal::RIGHT);
	}

	void moveDown();

	void drop();

	void rotateClockwise() {
		SuperRotationSystem::rotateTetromino(currentTetromino, matrix, Direction::Rotation::CLOCKWISE);
	}

	void rotateCounterclockwise() {
		SuperRotationSystem::rotateTetromino(currentTetromino, matrix, Direction::Rotation::COUNTERCLOCKWISE);
	}

	void swap();

	constexpr Matrix& getReferenceToMatrix() {
		return matrix;
	}

	int getScore() {
		return linesCleared;
	}

private:
	void gameOver();
	void spawnNextTetromino();

	unsigned int linesCleared = 0;
	bool currentHasBeenSwapped = false;

	Matrix matrix;
	Tetromino currentTetromino;
	Tetromino ghostTetromino;
	Tetromino nextTetromino;
	Tetromino storedTetromino;
};

#endif
