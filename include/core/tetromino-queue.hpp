#ifndef TETROMINO_QUEUE_H
#define TETROMINO_QUEUE_H
#include "core/tetromino.hpp"
#include <random>

class TetrominoQueue {
public:
	explicit TetrominoQueue(std::mt19937& gen)
		: gen(gen),
	{
		fillNextQueue();
	};

	void switchToNext(Tetromino& current);

	void holdCurrent(Tetromino& current);

private:
	void fillNextQueue();

	int index = 0;
	std::array<Tetromino, 3> nextQueue;

	std::mt19937& gen;
	bool canSwapWithHold = true;
	Tetromino hold;
};

#endif
