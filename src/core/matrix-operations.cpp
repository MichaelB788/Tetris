#include "core/matrix-operations.hpp"

bool MatrixOperation::isRowComplete(TetrisMatrix& matrix, unsigned int row) {
	for (unsigned int col = 0; col < matrix.WIDTH; col++) {
		if (matrix(col, row) == TileState::EMPTY) return false;
	}
	return true;
}

bool MatrixOperation::isRowEmpty(TetrisMatrix& matrix, unsigned int row) {
	for (unsigned int col = 0; col < matrix.WIDTH; col++) {
		if (matrix(col, row) == TileState::GROUNDED) return false;
	}
	return true;
}

bool MatrixOperation::canPlace(Tetromino& piece, TetrisMatrix& matrix) {
  for (auto& coordinate : piece.m_coordinates) {
    if (matrix(coordinate) == TileState::GROUNDED || matrix(coordinate) == TileState::WALL) {
      return false;
    }
  }
  return true;
}

void MatrixOperation::place(Tetromino& piece, TetrisMatrix& matrix) {
  for (auto& coordinate : piece.m_coordinates) {
    matrix(coordinate) == TileState::ACTIVE;
  }
}

void MatrixOperation::remove(Tetromino& piece, TetrisMatrix& matrix) {
  for (auto& coordinate : piece.m_coordinates) {
    matrix(coordinate) == TileState::EMPTY;
  }
}

const std::vector<unsigned int> MatrixOperation::getCompletedRows(TetrisMatrix& matrix) {
	std::vector<unsigned int> completedRows;
	for (unsigned int row = 0; row < matrix.HEIGHT; row++) {
		if (MatrixOperation::isRowComplete(matrix, row)) completedRows.push_back(row);
	}
	return completedRows;
}

void MatrixOperation::clearRows(TetrisMatrix& matrix, const std::vector<unsigned int>& completedRows) {
  // Empty all of the rows in completed rows
	for (const auto& row: completedRows) {
		for (unsigned int col = 0; col < matrix.WIDTH; col++) {
			matrix(col, row) = TileState::EMPTY;
		}
	}

  // Bring down populated rows that were above completed rows (which are empty rows at this point)
  // NOTE: We start at the end of completedRows because we want to fix the rows of the board starting from the bottom
	for (unsigned int row = completedRows.back(); row > 0; row--) {
		int nextRow = row - 1;
		while (MatrixOperation::isRowEmpty(matrix, nextRow) && nextRow > -1) nextRow--;

		if (nextRow > -1) {
			for (unsigned int col = 0; col < matrix.WIDTH; col++) {
				matrix(col, row) = matrix(col, nextRow);
        matrix(col, nextRow) = TileState::EMPTY;
			}
		}
		else {
      break;
    }
	}
}