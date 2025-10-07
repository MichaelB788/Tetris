#ifndef TETROMINO_OPERATIONS_H
#define TETROMINO_OPERATIONS_H
#include <array>
#include <random>
#include "util/data-structures.hpp"
#include "core/tetromino.hpp"

namespace TetrominoOperation {
  void rotate(Tetromino& piece);
  void move(Tetromino& piece, Direction dir);
  Tetromino::Type generateRandomType();
}

#endif