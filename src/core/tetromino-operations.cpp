#include "core/tetromino-operations.hpp"

TetrominoType tetromino_operation::generateRandomType() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 6);
  return TetrominoType(distrib(gen));
}
