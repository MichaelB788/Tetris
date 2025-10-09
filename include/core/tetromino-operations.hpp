#ifndef TETROMINO_OPERATIONS_H
#define TETROMINO_OPERATIONS_H
#include <array>
#include <random>
#include "util/vector2.hpp"
#include "util/game-constants.hpp"
#include "core/tetromino.hpp"

namespace TetrominoOperation {
  void rotate(Tetromino& piece);
  void move(Tetromino& piece, Direction dir);
  Tetromino::Type generateRandomType();
}

#endif