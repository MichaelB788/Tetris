#include "core/matrix-operations.hpp"
#include "core/matrix.hpp"
#include <vector>

void matrix_operation::clear(Matrix& matrix) {
  for (unsigned int y = 0; y < matrix_dimensions::HEIGHT; y++) {
    for (unsigned int x = 0; x < matrix_dimensions::WIDTH; x++) {
      if (x == 0 || x == matrix_dimensions::WIDTH - 1) {
        matrix(x, y) = TileState::WALL;
      } else {
        matrix(x, y) = TileState::EMPTY;
      }
    }
  }
}

bool matrix_operation::rowIsComplete(Matrix& matrix, unsigned int row) {
	for (unsigned int col = 1; col < matrix_dimensions::WIDTH - 1; col++) {
		if (matrix(col, row) != TileState::GROUND) return false;
	}
	return true;
}

bool matrix_operation::rowIsPopulated(Matrix& matrix, unsigned int row) {
	unsigned int populatedTiles = 0;
	for (unsigned int col = 1; col < matrix_dimensions::WIDTH - 1; col++) {
		if (matrix(col, row) == TileState::GROUND) populatedTiles++;
	}
	return populatedTiles > 0 && populatedTiles < 10;
}

bool matrix_operation::rowIsEmpty(Matrix& matrix, unsigned int row) {
	for (unsigned int col = 1; col < matrix_dimensions::WIDTH - 1; col++) {
		if (matrix(col, row) != TileState::EMPTY) return false;
	}
	return true;
}

void matrix_operation::clearRow(Matrix& matrix, unsigned int row) {
	for (unsigned int col = 1; col < matrix_dimensions::WIDTH - 1; col++) {
		matrix(col, row) = TileState::EMPTY;
	}
}

void matrix_operation::fillRow(Matrix& matrix, TileState tile, unsigned int row) {
	for (unsigned int col = 1; col < matrix_dimensions::WIDTH - 1; col++) {
		matrix(col, row) = tile;
	}
}

bool matrix_operation::canPlaceTetromino(std::array<Vector2, 4>& coordinates, Matrix& matrix) {
  for (auto& coordinate : coordinates) {
		if (coordinate.x < 0 || coordinate.y < 0 || coordinate.x >= matrix_dimensions::WIDTH || coordinate.y >= matrix_dimensions::HEIGHT) {
			return false;
		} else if (matrix(coordinate) == TileState::GROUND || matrix(coordinate) == TileState::WALL) {
      return false;
    }
  }
  return true;
}

void matrix_operation::placeTetromino(std::array<Vector2, 4>& coordinates, Matrix& matrix) {
  for (auto& coordinate : coordinates) {
    matrix(coordinate) = TileState::ACTIVE;
  }
}

void matrix_operation::removeTetromino(std::array<Vector2, 4>& coordinates, Matrix& matrix) {
  for (auto& coordinate : coordinates) {
    matrix(coordinate) = TileState::EMPTY;
  }
}

void matrix_operation::dropFloatingRows(Matrix& matrix) {
	for (unsigned int emptyRow = matrix_dimensions::HEIGHT - 1; emptyRow > 0; emptyRow--) {
		if (rowIsEmpty(matrix, emptyRow)) {
			int nextRow = emptyRow - 1;

			while (nextRow > -1) {
				if (rowIsEmpty(matrix, nextRow)) nextRow--;
				else break;
			}

			if (nextRow > -1) {
				for (unsigned int x = 1; x < matrix_dimensions::WIDTH - 1; x++) {
					matrix(x, emptyRow) = matrix(x, nextRow);
					matrix(x, nextRow) = TileState::EMPTY;
				}
			} else {
				break;
			}
		}
	}
}

void matrix_operation::clearCompletedRows(Matrix& matrix) {
	for (unsigned int y = 0; y < matrix_dimensions::HEIGHT; y++) {
		if (rowIsComplete(matrix, y)) {
			for (unsigned int x = 1; x < matrix_dimensions::WIDTH - 1; x++) {
				matrix(x, y) = TileState::EMPTY;
			}
		}
	}
}
