#include "Tetromino.hpp"
#include <random>

Tetromino Tetromino::random_piece() {
  thread_local std::mt19937 rng(std::random_device{}());
  thread_local std::uniform_int_distribution distribution(0, 6);

  return {static_cast<Type>(distribution(rng))};
}

void Tetromino::rotate_clockwise() {
  if (type_ == O)
    return;

  const Point pivot = shape_.front();
  for (auto &tile : shape_) {
    Point delta = tile - pivot;
    tile.x = pivot.x - delta.y;
    tile.y = pivot.y + delta.x;
  }
  rotation_ = rotation_ == R270 ? R0 : static_cast<Rotation>(rotation_ + 1);
}

void Tetromino::rotate_counterclockwise() {
  if (type_ == O)
    return;

  const Point pivot = shape_.front();
  for (auto &tile : shape_) {
    Point delta = tile - pivot;
    tile.x = pivot.x + delta.y;
    tile.y = pivot.y - delta.x;
  }
  rotation_ = rotation_ == R0 ? R270 : static_cast<Rotation>(rotation_ - 1);
}
