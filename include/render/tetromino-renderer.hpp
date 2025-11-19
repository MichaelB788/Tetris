#ifndef TETROMINO_RENDERER_H
#define TETROMINO_RENDERER_H
#include "core/tetromino.hpp"

class TetrominoRenderer {
public:
	TetrominoRenderer(const Tetromino& storedTetromino, const Tetromino& nextTetromino)
		: stored(storedTetromino),
			next(nextTetromino)
	{}

	void render(int posX);

private:
	const Tetromino& stored;
	const Tetromino& next;
};

#endif
