#pragma once
#include "core/Tetromino.hpp"
#include <cstddef>
#include <random>

class NextQueue {
public:
  void shuffle(std::mt19937 &rng);

  [[nodiscard]] Tetromino::Type pop(std::mt19937 &rng);

  [[nodiscard]] Tetromino::Type peek() const { return buffer_[read_]; }

private:
  std::array<Tetromino::Type, Tetromino::NUM_TETROMINO> buffer_{
      Tetromino::I, Tetromino::O, Tetromino::T, Tetromino::S,
      Tetromino::Z, Tetromino::J, Tetromino::L};

  size_t read_ = 0;
};
