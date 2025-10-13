#include "core/matrix-operations.hpp"
#include "core/matrix.hpp"
#include <vector>

void MatrixOperation::clear(Matrix& matrix) {
  for (unsigned int y = 0; y < MatrixDimensions::HEIGHT; y++) {
    for (unsigned int x = 0; x < MatrixDimensions::WIDTH; x++) {
      if (x == 0 || x == MatrixDimensions::WIDTH - 1) {
        matrix(x, y) = TileState::WALL;
      } else {
        matrix(x, y) = TileState::EMPTY;
      }
    }
  }
}

bool MatrixOperation::rowIsComplete(Matrix& matrix, unsigned int row) {
	for (unsigned int col = 1; col < MatrixDimensions::WIDTH - 1; col++) {
		if (matrix(col, row) != TileState::GROUND) return false;
	}
	return true;
}

bool MatrixOperation::rowIsPopulated(Matrix& matrix, unsigned int row) {
	unsigned int populatedTiles = 0;
	for (unsigned int col = 1; col < MatrixDimensions::WIDTH - 1; col++) {
		if (matrix(col, row) == TileState::GROUND) populatedTiles++;
	}
	return populatedTiles > 0 && populatedTiles < 10;
}

bool MatrixOperation::rowIsEmpty(Matrix& matrix, unsigned int row) {
	for (unsigned int col = 1; col < MatrixDimensions::WIDTH - 1; col++) {
		if (matrix(col, row) != TileState::EMPTY) return false;
	}
	return true;
}

void MatrixOperation::clearRow(Matrix& matrix, unsigned int row) {
	for (unsigned int col = 1; col < MatrixDimensions::WIDTH - 1; col++) {
		matrix(col, row) = TileState::EMPTY;
	}
}

void MatrixOperation::fillRow(Matrix& matrix, TileState tile, unsigned int row) {
	for (unsigned int col = 1; col < MatrixDimensions::WIDTH - 1; col++) {
		matrix(col, row) = tile;
	}
}

bool MatrixOperation::canPlaceTetromino(Tetromino& piece, Matrix& matrix) {
  for (auto& coordinate : piece.m_coordinates) {
    if (matrix(coordinate) == TileState::GROUND || matrix(coordinate) == TileState::WALL) {
      return false;
    }
  }
  return true;
}

void MatrixOperation::placeTetromino(Tetromino& piece, Matrix& matrix) {
  for (auto& coordinate : piece.m_coordinates) {
    matrix(coordinate) = TileState::ACTIVE;
  }
}

void MatrixOperation::removeTetromino(Tetromino& piece, Matrix& matrix) {
  for (auto& coordinate : piece.m_coordinates) {
    matrix(coordinate) = TileState::EMPTY;
  }
}

void MatrixOperation::dropFloatingRows(Matrix& matrix) {
	for (unsigned int emptyRow = MatrixDimensions::HEIGHT - 1; emptyRow > 0; emptyRow--) {
		if (rowIsEmpty(matrix, emptyRow)) {
			int nextRow = emptyRow - 1;

			while (nextRow > -1) {
				if (rowIsEmpty(matrix, nextRow)) nextRow--;
				else break;
			}

			if (nextRow > -1) {
				for (unsigned int x = 1; x < MatrixDimensions::WIDTH - 1; x++) {
					matrix(x, emptyRow) = matrix(x, nextRow);
					matrix(x, nextRow) = TileState::EMPTY;
				}
			} else {
				break;
			}
		}
	}
}

void MatrixOperation::clearCompletedRows(Matrix& matrix) {
	for (unsigned int y = 0; y < MatrixDimensions::HEIGHT; y++) {
		if (rowIsComplete(matrix, y)) {
			for (unsigned int x = 1; x < MatrixDimensions::WIDTH - 1; x++) {
				matrix(x, y) = TileState::EMPTY;
			}
		}
	}
}
