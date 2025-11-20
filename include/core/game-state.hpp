#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include "core/tetromino-movement.hpp"
#include "core/super-rotation-system.hpp"
#include <random>

class GameState {
public:
	GameState(std::mt19937& gen)
		: gen(gen)
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

	const Matrix& getMatrix() const { return matrix; }

	const Tetromino& getStored() const { return storedTetromino; }

	const Tetromino& getNext() const { return nextTetromino; }

	const int getScore() const { return linesCleared; }

private:
	void gameOver();
	void spawnNext();

	unsigned int linesCleared = 0;
	bool swapUsedThisTurn = false;
	std::mt19937& gen;

	Matrix matrix;
	Tetromino currentTetromino;
	Tetromino nextTetromino;
	Tetromino storedTetromino;
};

#endif
