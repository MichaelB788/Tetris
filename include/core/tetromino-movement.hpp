#ifndef TETROMINO_MOVEMENT_H
#define TETROMINO_MOVEMENT_H
#include "tetromino.hpp"
#include "matrix.hpp"

/// @brief Controls the movement of a Tetromino actor within the Matrix. 
namespace TetrominoMovement {
	/// @brief Removes the current Tetromino from the board, shifting it horizontally should it not collide impermeable tiles.
	void moveTetromino(Tetromino& current, Matrix& matrix, Direction::Horizontal direction);

	/* *
	 * @brief Removes the current Tetromino from the board, shifting it down should it not collide an impermeable.
	 * @return true if the Tetromino has moved down and placed on the Matrix, false if it has collided an impermeable.
	 * */
	bool moveTetrominoDown(Tetromino& current, Matrix& matrix);

	/// @brief Removes the current Tetromino from the matrix, updates the Tetromino's position to the lowest row it can inhabit.
	void dropTetromino(Tetromino& current, Matrix& matrix);
};

#endif
