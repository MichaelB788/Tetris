#include "Tetromino.hpp"
#include <algorithm>
#include <random>

Tetromino Tetromino::random_piece() {
  static std::mt19937 rng(std::random_device{}());
  static std::uniform_int_distribution distribution(0, 6);

  return {static_cast<Type>(distribution(rng))};
}

Tetromino::Shape Tetromino::shape() const {
  Shape shape{};
  std::ranges::transform(SHAPES[type_][rotation_], shape.begin(),
                         [this](Point p) { return pos_ + p; });
  return shape;
}
