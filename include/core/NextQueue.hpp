#pragma once
#include "core/Tetromino.hpp"
#include <cassert>
#include <cstddef>
#include <random>

class NextQueue {
public:
  void shuffle(std::mt19937 &rng);

  [[nodiscard]] Tetromino::Type pop() {
    assert(!empty() && "Cannot pop, queue is empty");
    return buffer_[read_++];
  }

  [[nodiscard]] bool empty() const { return read_ == buffer_.size(); }

  [[nodiscard]] Tetromino::Type peek() const {
    assert(!empty() && "Cannot peek, queue is empty");
    return buffer_[read_];
  }

private:
  std::array<Tetromino::Type, Tetromino::NUM_TETROMINO> buffer_{
      Tetromino::I, Tetromino::O, Tetromino::T, Tetromino::S,
      Tetromino::Z, Tetromino::J, Tetromino::L};

  size_t read_ = 0;
};
