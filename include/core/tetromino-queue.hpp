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
	
	const Tetromino& getHold() const { return hold; }

	bool isHoldEmpty() const { return hold.isNull(); }
	
	bool isCurrentHeld() const { return currentIsHeld; }

	const RingBuffer<Tetromino, 5> getNextQueue() const { return nextQueue; }

	void switchToNext(Tetromino& current);

	void holdCurrent(Tetromino& current);

	void reset();

private:
	void fillNextQueue();

	RingBuffer<Tetromino, 5> nextQueue;

	bool currentIsHeld = false;
	Tetromino hold;

	std::mt19937& gen;
};

#endif
