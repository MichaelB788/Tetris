#ifndef TETROMINO_OPERATIONS_H
#define TETROMINO_OPERATIONS_H
#include <array>
#include <random>
#include "util/vector2.hpp"
#include "util/game-constants.hpp"
#include "core/tetromino.hpp"

namespace tetromino_operation {
  void move(Tetromino& piece, Direction dir);
  void rotate(Tetromino& piece);
  Tetromino::Type generateRandomType();
}

#endif
