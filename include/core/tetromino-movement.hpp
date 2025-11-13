#ifndef TETROMINO_MOVEMENT_H
#define TETROMINO_MOVEMENT_H
#include "tetromino.hpp"
#include "matrix.hpp"

/// @brief Controls the movement of a Tetromino actor within the Matrix. 
namespace TetrominoMovement {
	bool moveTetromino(Tetromino& actor, Matrix& scene, Direction::Horizontal direction);
	bool moveTetrominoDown(Tetromino& actor, Matrix& scene);
	void dropTetromino(Tetromino& actor, Matrix& scene);
};

#endif
