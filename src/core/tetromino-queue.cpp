#include "core/tetromino-queue.hpp"

void TetrominoQueue::switchToNext(Tetromino& current) {
	currentIsHeld = false;
	current = nextQueue[index];
	nextQueue[index] = Tetromino::getRandomTetromino(gen);
	index = index + 1 % nextQueue.size();
}

void TetrominoQueue::holdCurrent(Tetromino& current) {
	if ( !currentIsHeld ) {
		currentIsHeld = true;
		std::swap(current, hold);
		if ( current.isNull() ) switchToNext(current);
	}
}

void TetrominoQueue::reset() {
	fillNextQueue(gen);
	hold = Tetromino(Tetromino::Type::NONE);
}
