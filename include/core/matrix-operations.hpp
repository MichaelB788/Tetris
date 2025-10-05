#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H
#include <vector>
#include "util/data-structures.hpp"
#include "util/game-constants.hpp"

/// @brief Manages the Tetris matrix (playfield) state and operations.
namespace MatrixOperation {
	inline void clear(TetrisMatrix& matrix) { for (uint8_t x = 0; x < matrix.WIDTH; x++) for (uint8_t y = 0; y < matrix.HEIGHT; y++) matrix(x, y) = TileState::EMPTY; };
	bool isRowComplete(TetrisMatrix& matrix, unsigned int row);
	bool isRowEmpty(TetrisMatrix& matrix, unsigned int row);

  /**
   * @brief Searches the matrix top-down to find rows that are full.
   * @return std::vector<unsigned int> row: indexes containing completed rows, sorted by highest to lowest.
   **/ 
  const std::vector<unsigned int> getCompletedRows(TetrisMatrix& matrix);

  /// @note to be used with MatrixOperation::getCompletedRows
	void clearRows(TetrisMatrix& matrix, const std::vector<unsigned int>& completedRows);
};

#endif