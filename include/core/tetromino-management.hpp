#ifndef TETROMINO_MANAGEMENT_H
#define TETROMINO_MANAGEMENT_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include <utility>

namespace TetrominoManagement {
	/* *
	 * @brief Sets current to next, pushing the new current up while there's ground tiles below.
	 * @return bool Whether the Tetromino can be placed in the Matrix after a switch. 
	 * */
	bool switchToNext(Tetromino& current, Tetromino& next, Matrix& matrix);

	/* *
	 * @brief Swaps current with stored, pushing the new current up while there's ground tiles below.
	 * @return bool Whether the Tetromino can be placed in the Matrix after a swap. 
	 * */
	bool swapWithHold(Tetromino& current, Tetromino& stored, Matrix& matrix);

	Tetromino generateRandomTetromino();

	Tetromino generateNullTetromino();
}

#endif
