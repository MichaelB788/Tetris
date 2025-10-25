#include "core/matrix.hpp"

Matrix::Matrix() {
  for (unsigned int y = 0; y < matrix_dimensions::HEIGHT; y++) {
    for (unsigned int x = 0; x < matrix_dimensions::WIDTH; x++) {
      if (x == 0 || x == matrix_dimensions::WIDTH - 1) {
        m_data[computeFlatIndex(x, y)] = TileState::WALL;
      } else {
        m_data[computeFlatIndex(x, y)] = TileState::EMPTY;
      }
    }
  }
}
