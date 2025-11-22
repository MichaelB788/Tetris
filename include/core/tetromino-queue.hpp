#ifndef TETROMINO_QUEUE_H
#define TETROMINO_QUEUE_H
#include "core/tetromino.hpp"
#include "util/circular-array.hpp"
#include <random>

class TetrominoQueue {
public:
	explicit TetrominoQueue(std::mt19937& gen) : gen(gen) {
		fillNextQueue(gen);
	}

	void switchToNext(Tetromino& current);

	void holdCurrent(Tetromino& current);

	void reset();

private:
	void fillNextQueue(std::mt19937& gen) {
		for (auto& tetromino : nextQueue) tetromino = Tetromino(Tetromino::getRandomType(gen));
	};

	CircularArray<Tetromino, 4> nextQueue;

	std::mt19937& gen;
	bool currentIsHeld = false;
	Tetromino hold;
};

#endif
