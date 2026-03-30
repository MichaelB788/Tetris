#include "Tetromino.hpp"
#include <algorithm>
#include <random>

namespace {
constexpr Point SHAPES[Tetromino::NUM_TETROMINO][Tetromino::NUM_ROTATION][4]{
    // I
    {{{-1, 0}, {0, 0}, {1, 0}, {2, 0}},  // R0
     {{0, -1}, {0, 0}, {0, 1}, {0, 2}},  // R90
     {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},  // R180
     {{0, -1}, {0, 0}, {0, 1}, {0, 2}}}, // R90

    // O
    {{{0, 0}, {1, 0}, {0, -1}, {1, -1}},  // R0
     {{0, 0}, {1, 0}, {0, -1}, {1, -1}},  // R90
     {{0, 0}, {1, 0}, {0, -1}, {1, -1}},  // R180
     {{0, 0}, {1, 0}, {0, -1}, {1, -1}}}, // R270

    // T
    {{{-1, 0}, {0, 0}, {1, 0}, {0, -1}},  // R0
     {{0, 1}, {0, 0}, {0, -1}, {1, 0}},   // R90
     {{-1, 0}, {0, 0}, {1, 0}, {0, 1}},   // R180
     {{0, 1}, {0, 0}, {0, -1}, {-1, 0}}}, // R270

    // S
    {{{-1, 0}, {0, 0}, {0, -1}, {1, -1}},  // R0
     {{0, -1}, {0, 0}, {1, 0}, {1, 1}},    // R90
     {{-1, 1}, {0, 1}, {0, 0}, {1, 0}},    // R180
     {{-1, -1}, {-1, 0}, {0, 0}, {0, 1}}}, // R270

    // Z
    {{{-1, -1}, {0, -1}, {0, 0}, {1, 0}},  // R0
     {{0, 1}, {0, 0}, {1, 0}, {1, -1}},    // R90
     {{-1, 0}, {0, 0}, {0, 1}, {1, 1}},    // R180
     {{-1, 1}, {-1, 0}, {0, 0}, {0, -1}}}, // R270

    // J
    {{{-1, 0}, {0, 0}, {1, 0}, {-1, -1}}, // R0
     {{0, 1}, {0, 0}, {0, -1}, {1, -1}},  // R90
     {{-1, 0}, {0, 0}, {1, 0}, {1, 1}},   // R180
     {{0, 1}, {0, 0}, {0, -1}, {-1, 1}}}, // R270

    // L
    {{{-1, 0}, {0, 0}, {1, 0}, {1, -1}},   // R0
     {{0, -1}, {0, 0}, {0, 1}, {1, 1}},    // R90
     {{-1, 0}, {0, 0}, {1, 0}, {-1, 1}},   // R180
     {{0, -1}, {0, 0}, {0, 1}, {-1, -1}}}, // R270
};
}

Tetromino::Type Tetromino::random_type() {
  static std::mt19937 rng(std::random_device{}());
  static std::uniform_int_distribution distribution(0, 6);

  return static_cast<Type>(distribution(rng));
}

Tetromino::Shape Tetromino::test_shift(Point delta) const {
  Shape test{};
  std::ranges::transform(SHAPES[type_][rotation_], test.begin(),
                         [&](Point p) { return pos_ + p + delta; });
  return test;
}

Tetromino::Shape Tetromino::shape() const {
  Shape shape{};
  std::ranges::transform(SHAPES[type_][rotation_], shape.begin(),
                         [this](Point p) { return pos_ + p; });
  return shape;
}
