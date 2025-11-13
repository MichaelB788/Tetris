#ifndef TETROMINO_MANAGEMENT_H
#define TETROMINO_MANAGEMENT_H

#include "core/matrix.hpp"
#include "core/tetromino.hpp"
namespace TetrominoManagement {
	bool switchToNext(Tetromino& currentTetromino, Tetromino& nextTetromino, Matrix& matrix);

	void swapWithHold(Tetromino& currentTetromino, Tetromino& storedTetromino, Matrix& matrix);

	Tetromino generateRandomTetromino();

	Tetromino generateNullTetromino();
}

#endif
