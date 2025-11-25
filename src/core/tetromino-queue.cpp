#include "core/tetromino-queue.hpp"

void TetrominoQueue::switchToNext(Tetromino& current) {
	current = nextQueue.peek();
	nextQueue.pop();
	nextQueue.push(Tetromino::getRandomTetromino(gen));
	currentIsHeld = false;
}

void TetrominoQueue::holdCurrent(Tetromino& current) {
	std::swap(current, hold);
	hold.move({0, 0});
	if ( current.isNull() ) switchToNext(current);
	currentIsHeld = true;
}

void TetrominoQueue::reset() {
	fillNextQueue();
	hold = Tetromino(Tetromino::Type::NONE);
}

void TetrominoQueue::fillNextQueue() {
	nextQueue.clear();
	for (int i = 0; i < nextQueue.max_size(); i++) {
		nextQueue.push(Tetromino::getRandomTetromino(gen));
	}
}
