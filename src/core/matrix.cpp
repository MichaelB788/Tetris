#include "core/matrix.hpp"

Matrix::Matrix() {
  for (unsigned int y = 0; y < MatrixDimensions::HEIGHT; y++) {
    for (unsigned int x = 0; x < MatrixDimensions::WIDTH; x++) {
      if (x == 0 || x == MatrixDimensions::WIDTH - 1) {
        m_data[computeFlatIndex(x, y)] = TileState::WALL;
      } else if (y == MatrixDimensions::HEIGHT - 1) {
        m_data[computeFlatIndex(x, y)] = TileState::GROUND;
      } else {
        m_data[computeFlatIndex(x, y)] = TileState::EMPTY;
      }
    }
  }
}
