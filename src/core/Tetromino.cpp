#include "core/Tetromino.hpp"
#include <algorithm>

namespace {
/**
 * All possible rotational states of each Tetromino. The data can be parsed via
 * the following pattern:
 *
 * SHAPES[TetrominoType][TetrominoRotation][BlockIndex]
 */
constexpr Point SHAPES[7][4][4]{
    // I
    {{{-1, 0}, {0, 0}, {1, 0}, {2, 0}},   // R0
     {{0, -1}, {0, 0}, {0, 1}, {0, 2}},   // R90
     {{-2, 0}, {-1, 0}, {0, 0}, {1, 0}},  // R180
     {{0, 1}, {0, 0}, {0, -1}, {0, -2}}}, // R90

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
} // namespace

auto tetromino::shape_of(Tetromino tetromino) -> Tetromino::Shape {
  Tetromino::Shape shape{};
  std::ranges::transform(SHAPES[tetromino.type][tetromino.rotation],
                         shape.begin(),
                         [&](Point origin) { return tetromino.pos + origin; });
  return shape;
}

auto tetromino::shape_at(Tetromino tetromino, Point pos) -> Tetromino::Shape {
  Tetromino::Shape shape{};
  std::ranges::transform(SHAPES[tetromino.type][tetromino.rotation],
                         shape.begin(),
                         [&](Point origin) { return pos + origin; });
  return shape;
}

auto tetromino::rotated_clockwise(Tetromino tetromino) -> Tetromino {
  tetromino.rotation =
      static_cast<Tetromino::Rotation>((tetromino.rotation + 1) % 4);
  return tetromino;
}

auto tetromino::rotated_counterclockwise(Tetromino tetromino) -> Tetromino {
  tetromino.rotation =
      static_cast<Tetromino::Rotation>((tetromino.rotation + 3) % 4);
  return tetromino;
}

auto tetromino::rotated_half_turn(Tetromino tetromino) -> Tetromino {
  tetromino.rotation =
      static_cast<Tetromino::Rotation>((tetromino.rotation + 2) % 4);
  return tetromino;
}
