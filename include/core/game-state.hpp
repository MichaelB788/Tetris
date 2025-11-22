#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include "core/tetromino-movement.hpp"
#include "core/super-rotation-system.hpp"
#include "core/tetromino-queue.hpp"
#include <random>

class GameState {
public:
	GameState(std::mt19937& gen)
		: gen(gen),
			current(Tetromino(Tetromino::getRandomType(gen))),
			tetrominoQueue(gen)
	{}

	void moveLeft() {
		TetrominoMovement::moveTetromino(current, matrix, Direction::Horizontal::LEFT);
	}

	void moveRight() {
		TetrominoMovement::moveTetromino(current, matrix, Direction::Horizontal::RIGHT);
	}

	void moveDown();

	void drop() {
		TetrominoMovement::dropTetromino(current, matrix); spawnNext();
	}

	void rotateClockwise() {
		SuperRotationSystem::rotateTetromino(current, matrix, Direction::Rotation::CLOCKWISE);
	}

	void rotateCounterclockwise() {
		SuperRotationSystem::rotateTetromino(current, matrix, Direction::Rotation::COUNTERCLOCKWISE);
	}

	void hold() {
		tetrominoQueue.holdCurrent(current); spawnNext();
	}

	const Matrix& getMatrix() const { return matrix; }

	const TetrominoQueue& getQueue() const { return tetrominoQueue; }

	const int getScore() const { return linesCleared; }

private:
	void gameOver();

	void spawnNext();

	unsigned int linesCleared = 0;
	std::mt19937& gen;

	Matrix matrix;
	Tetromino current;
	TetrominoQueue tetrominoQueue;
};

#endif
