#include "Tetromino.hpp"
#include <random>

namespace {
constexpr std::array<std::array<Point, 4>, 7> shapes{{
    {{{0, 0}, {-1, 0}, {1, 0}, {2, 0}}},   // I
    {{{0, 0}, {1, 0}, {0, -1}, {1, -1}}},  // O
    {{{0, 0}, {-1, 0}, {1, 0}, {0, -1}}},  // T
    {{{0, 0}, {-1, 0}, {0, -1}, {1, -1}}}, // S
    {{{0, 0}, {-1, -1}, {0, -1}, {1, 0}}}, // Z
    {{{0, 0}, {-1, -1}, {-1, 0}, {1, 0}}}, // J
    {{{0, 0}, {1, -1}, {1, 0}, {-1, 0}}}   // L
}};
} // namespace

Tetromino::Tetromino()
    : type_(TetrominoType::I), blocks_(shapes[type_index()]) {}

Tetromino::Tetromino(const TetrominoType type, Point pos)
    : type_(type), blocks_(shapes[type_index()]), rotation_state_(0, 0) {
  set_position(pos);
}

TetrominoType Tetromino::get_random_type() {
  thread_local std::mt19937 rng(std::random_device{}());
  thread_local std::uniform_int_distribution distribution(0, 6);
  return static_cast<TetrominoType>(distribution(rng));
}

void Tetromino::shift(const Point delta) {
  for (auto &tile : blocks_)
    tile += delta;
}

void Tetromino::set_position(const Point pos) {
  const Point delta = pos - blocks_.front();
  for (auto &tile : blocks_)
    tile += delta;
}

void Tetromino::rotate_clockwise() {
  for (auto &tile : blocks_)
    tile = tile.rotate_clockwise(blocks_.front());
  rotation_state_.clockwise();
}

void Tetromino::rotate_counterclockwise() {
  for (auto &tile : blocks_)
    tile = tile.rotate_counterclockwise(blocks_.front());
  rotation_state_.counterclockwise();
}

void Tetromino::RotationState::clockwise() {
  prev = curr;
  curr = (curr + 1) % 4;
}

void Tetromino::RotationState::counterclockwise() {
  prev = curr;
  curr = curr == 0 ? 3 : curr - 1;
}
