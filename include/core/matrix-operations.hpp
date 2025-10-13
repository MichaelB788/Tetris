#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H
#include "util/vector2.hpp"
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

/// @brief Manages the Tetris matrix (playfield) state and operations.
namespace MatrixOperation {
	void clear(Matrix& matrix);

	bool rowIsComplete(Matrix& matrix, unsigned int row);
	bool rowIsPopulated(Matrix& matrix, unsigned int row);
	bool rowIsEmpty(Matrix& matrix, unsigned int row);

	void clearRow(Matrix& matrix, unsigned int row);
	void fillRow(Matrix& matrix, TileState tile, unsigned int row);

  bool canPlaceTetromino(Tetromino& piece, Matrix& matrix);
  void placeTetromino(Tetromino& piece, Matrix& matrix);
  void removeTetromino(Tetromino& piece, Matrix& matrix);

	void dropFloatingRows(Matrix& matrix);
	void clearCompletedRows(Matrix& matrix);
};

#endif
