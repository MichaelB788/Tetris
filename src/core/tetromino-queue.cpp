#include "core/tetromino-queue.hpp"

void TetrominoQueue::switchToNext(Tetromino& current) {
	current = nextQueue.peek();
	nextQueue.pop();

	Tetromino next = Tetromino::getRandomTetromino(gen);
	while (nextQueue.peek_last() == next) next = Tetromino::getRandomTetromino(gen);

	nextQueue.push(next);
	currentIsHeld = false;
}

void TetrominoQueue::holdCurrent(Tetromino& current) {
	current.rotateToOriginalState();
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
		Tetromino next = Tetromino::getRandomTetromino(gen);
		if (!nextQueue.empty()) {
			while (nextQueue.peek_last() == next) next = Tetromino::getRandomTetromino(gen);
		}
		nextQueue.push(next);
	}
}
