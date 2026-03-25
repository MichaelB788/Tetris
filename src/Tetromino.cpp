#include "Tetromino.hpp"
#include <cstdint>
#include <random>

Tetromino::Tetromino(Type t) : type_(t), rotation_(0) {
  static constexpr std::array<std::array<Point, 4>, 7> shapes{{
      {{{0, 0}, {-1, 0}, {1, 0}, {2, 0}}},   // I
      {{{0, 0}, {1, 0}, {0, -1}, {1, -1}}},  // O
      {{{0, 0}, {-1, 0}, {1, 0}, {0, -1}}},  // T
      {{{0, 0}, {-1, 0}, {0, -1}, {1, -1}}}, // S
      {{{0, 0}, {-1, -1}, {0, -1}, {1, 0}}}, // Z
      {{{0, 0}, {-1, -1}, {-1, 0}, {1, 0}}}, // J
      {{{0, 0}, {1, -1}, {1, 0}, {-1, 0}}}   // L
  }};

  blocks_ = shapes[static_cast<uint8_t>(type_)];
}

Tetromino Tetromino::rand() {
  thread_local std::mt19937 rng(std::random_device{}());
  thread_local std::uniform_int_distribution distribution(0, 6);

  return {static_cast<Type>(distribution(rng))};
}

void Tetromino::rotate_clockwise() {
  if (type_ == Type::O)
    return;

  const Point pivot = blocks_.front();
  for (auto &tile : blocks_) {
    Point delta = tile - pivot;
    tile.x = pivot.x - delta.y;
    tile.y = pivot.y + delta.x;
  }
  rotation_ = rotation_ == 3 ? 0 : rotation_ + 1;
}

void Tetromino::rotate_counterclockwise() {
  if (type_ == Type::O)
    return;

  const Point pivot = blocks_.front();
  for (auto &tile : blocks_) {
    Point delta = tile - pivot;
    tile.x = pivot.x + delta.y;
    tile.y = pivot.y - delta.x;
  }
  rotation_ = rotation_ == 0 ? 3 : rotation_ - 1;
}
