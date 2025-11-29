#include "core/tetromino-queue.hpp"

void TetrominoQueue::switchToNext(Tetromino& current) {
	current = nextQueue.front();
	nextQueue.pop_front();

	Tetromino next = Tetromino::getRandomTetromino(gen);
	while (nextQueue.back() == next) next = Tetromino::getRandomTetromino(gen);

	nextQueue.push_back(next);
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
			while (nextQueue.back() == next) next = Tetromino::getRandomTetromino(gen);
		}
		nextQueue.push_back(next);
	}
}
