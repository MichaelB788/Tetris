#include "core/matrix-operations.hpp"
#include "core/matrix.hpp"
#include <vector>


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
					matrix(x, nextRow).clear();
				}
			} else {
				break;
			}
		}
	}
}

void matrix_operation::clearCompletedRows(Matrix& matrix) {
}
