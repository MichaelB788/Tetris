#include "core/Tetromino.hpp"
#include <algorithm>

namespace {
static constexpr size_t MAX_TETROMINO = 7;
static constexpr size_t MAX_ROTATIONS = 4;
static constexpr size_t BLOCKS = 4;

constexpr Point SHAPES[MAX_TETROMINO][MAX_ROTATIONS][BLOCKS]{
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

auto Tetromino::shifted(Point delta) const -> Shape {
  Shape shifted{};
  std::ranges::transform(SHAPES[type][rotation.value()], shifted.begin(),
                         [&](Point p) { return pos + p + delta; });
  return shifted;
}

auto Tetromino::shape() const -> Shape {
  Shape shape{};
  std::ranges::transform(SHAPES[type][rotation.value()], shape.begin(),
                         [this](Point p) { return pos + p; });
  return shape;
}
