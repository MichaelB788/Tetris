#include "core/matrix-operations.hpp"

void MatrixOperation::clear(Matrix& matrix) {
  for (unsigned int y = 0; y < MatrixDimensions::HEIGHT; y++) {
    for (unsigned int x = 0; x < MatrixDimensions::WIDTH; x++) {
      if (x == 0 || x == MatrixDimensions::WIDTH - 1) {
        matrix(x, y) = TileState::WALL;
      } else if (y == MatrixDimensions::HEIGHT - 1) {
        matrix(x, y) = TileState::GROUND;
      } else {
        matrix(x, y) = TileState::EMPTY;
      }
    }
  }
}

bool MatrixOperation::isRowComplete(Matrix& matrix, unsigned int row) {
	for (unsigned int col = 1; col < MatrixDimensions::WIDTH - 1; col++) {
		if (matrix(col, row) == TileState::EMPTY) return false;
	}
	return true;
}

bool MatrixOperation::isRowEmpty(Matrix& matrix, unsigned int row) {
	for (unsigned int col = 1; col < MatrixDimensions::WIDTH - 1; col++) {
		if (matrix(col, row) == TileState::GROUND) return false;
	}
	return true;
}

bool MatrixOperation::canPlace(Tetromino& piece, Matrix& matrix) {
  for (auto& coordinate : piece.m_coordinates) {
    if (matrix(coordinate) == TileState::GROUND || matrix(coordinate) == TileState::WALL) {
      return false;
    }
  }
  return true;
}

void MatrixOperation::place(Tetromino& piece, Matrix& matrix) {
  for (auto& coordinate : piece.m_coordinates) {
    matrix(coordinate) = TileState::ACTIVE;
  }
}

void MatrixOperation::remove(Tetromino& piece, Matrix& matrix) {
  for (auto& coordinate : piece.m_coordinates) {
    matrix(coordinate) = TileState::EMPTY;
  }
}

const std::vector<unsigned int> MatrixOperation::getCompletedRows(Matrix& matrix) {
	std::vector<unsigned int> completedRows;
	for (unsigned int row = 0; row < MatrixDimensions::HEIGHT - 1; row++) {
		if (MatrixOperation::isRowComplete(matrix, row)) completedRows.push_back(row);
	}
	return completedRows;
}

void MatrixOperation::clearRows(Matrix& matrix, const std::vector<unsigned int>& completedRows) {
  // Empty all of the rows in completed rows
	for (const auto& row: completedRows) {
		for (unsigned int col = 1; col < MatrixDimensions::WIDTH - 1; col++) {
			matrix(col, row) = TileState::EMPTY;
		}
	}

  // Bring down populated rows that were above completed rows (which are empty rows at this point)
  // NOTE: We start at the end of completedRows because we want to fix the rows of the board starting from the bottom
	for (unsigned int row = completedRows.back(); row > 0; row--) {
		int nextRow = row - 1;
		while (MatrixOperation::isRowEmpty(matrix, nextRow) && nextRow > -1) nextRow--;

		if (nextRow > -1) {
			for (unsigned int col = 1; col < MatrixDimensions::WIDTH - 1; col++) {
				matrix(col, row) = matrix(col, nextRow);
        matrix(col, nextRow) = TileState::EMPTY;
			}
		}
		else {
      break;
    }
	}
}
