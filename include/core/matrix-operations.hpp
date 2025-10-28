#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H
#include "util/vector2.hpp"
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include <array>

/// @brief Manages the Tetris matrix (playfield) state and operations.
namespace matrix_operation {
	void clear(Matrix& matrix);

	bool rowIsComplete(Matrix& matrix, unsigned int row);
	bool rowIsPopulated(Matrix& matrix, unsigned int row);
	bool rowIsEmpty(Matrix& matrix, unsigned int row);

	void clearRow(Matrix& matrix, unsigned int row);
	void fillRow(Matrix& matrix, MatrixTile tile, unsigned int row);

  bool isWithinBounds(const Vector2& coordinate, Matrix& matrix);

  inline void placeTetromino(Tetromino& actor, Matrix& matrix) {
		for (auto& coordinate : actor.coordinates())
			matrix(coordinate).occupy(actor.type());
	};

	void dropFloatingRows(Matrix& matrix);
	void clearCompletedRows(Matrix& matrix);
};

#endif
