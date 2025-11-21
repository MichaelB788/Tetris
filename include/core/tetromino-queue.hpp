#ifndef TETROMINO_QUEUE_H
#define TETROMINO_QUEUE_H
#include "core/tetromino.hpp"
#include <random>

class TetrominoQueue {
public:
	explicit TetrominoQueue(std::mt19937& gen) : gen(gen) {
		fillNextQueue(gen);
	}

	void switchToNext(Tetromino& current);

	void holdCurrent(Tetromino& current);

	void reset();

	// Iterator
	using const_iterator = std::array<Tetromino, 4>::const_iterator;

	const_iterator begin() const { return nextQueue.begin(); }

private:
	void fillNextQueue(std::mt19937& gen) {
		for (auto& tetromino : nextQueue) tetromino = Tetromino(Tetromino::getRandomType(gen));
	};

	uint8_t index = 0;
	std::array<Tetromino, 4> nextQueue;

	std::mt19937& gen;
	bool currentIsHeld = false;
	Tetromino hold;
};

#endif
