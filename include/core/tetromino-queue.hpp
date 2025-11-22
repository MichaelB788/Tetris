#ifndef TETROMINO_QUEUE_H
#define TETROMINO_QUEUE_H
#include "core/tetromino.hpp"
#include "util/ring-buffer.hpp"
#include <random>

class TetrominoQueue {
public:
	explicit TetrominoQueue(std::mt19937& gen) : gen(gen) {
		fillNextQueue();
	}

	void switchToNext(Tetromino& current);

	void holdCurrent(Tetromino& current);

	void reset();

private:
	void fillNextQueue() {
		for (auto& tetromino : nextQueue) tetromino = Tetromino::getRandomTetromino(gen);
	};

	RingBuffer<Tetromino, 4> nextQueue;

	std::mt19937& gen;
	bool currentIsHeld = false;
	Tetromino hold;
};

#endif
