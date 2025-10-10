#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H
#include <vector>
#include "util/vector2.hpp"
#include "util/game-constants.hpp"
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

/// @brief Manages the Tetris matrix (playfield) state and operations.
namespace MatrixOperation {
	void clear(Matrix& matrix);
	bool isRowComplete(Matrix& matrix, unsigned int row);
	bool isRowEmpty(Matrix& matrix, unsigned int row);
  bool canPlace(Tetromino& piece, Matrix& matrix);
  void place(Tetromino& piece, Matrix& matrix);
  void remove(Tetromino& piece, Matrix& matrix);

  /**
   * @brief Searches the matrix top-down to find rows that are full.
   * @return std::vector<unsigned int> row: indexes containing completed rows, sorted by highest to lowest.
   **/ 
  const std::vector<unsigned int> getCompletedRows(Matrix& matrix);

  /// @note to be used with MatrixOperation::getCompletedRows
	void clearRows(Matrix& matrix, const std::vector<unsigned int>& completedRows);
};

#endif
