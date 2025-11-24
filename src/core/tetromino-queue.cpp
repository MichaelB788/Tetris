#include "core/tetromino-queue.hpp"

void TetrominoQueue::switchToNext(Tetromino& current) {
	current = *nextQueue.peek();
	nextQueue.pop();
	nextQueue.push(Tetromino::getRandomTetromino(gen));
	currentIsHeld = false;
}

void TetrominoQueue::holdCurrent(Tetromino& current) {
	if ( !currentIsHeld ) {
		std::swap(current, hold);
		if ( current.isNull() ) switchToNext(current);
		currentIsHeld = true;
	}
}

void TetrominoQueue::reset() {
	fillNextQueue();
	hold = Tetromino(Tetromino::Type::NONE);
}
