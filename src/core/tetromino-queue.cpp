#include "core/tetromino-queue.hpp"

void TetrominoQueue::switchToNext(Tetromino& current) {
	current = nextQueue[index];
	nextQueue[index] = Tetromino(Tetromino::getRandomType(gen), {0, 0});
	index = index + 1 % nextQueue.size();
}

void TetrominoQueue::holdCurrent(Tetromino& current) {
	std::swap(current, hold);
	if ( current.isNull() ) switchToNext(current);
}
