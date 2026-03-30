#pragma once
#include "core/Tetromino.hpp"
#include "util/CircularBuffer.hpp"

class NextQueue {
public:
  NextQueue() { shuffle(); }

  void shuffle();

  [[nodiscard]] Tetromino::Type pop();

  [[nodiscard]] const auto &buffer() const { return buffer_; }

private:
  void push_random();

  CircularBuffer<Tetromino::Type, 5> buffer_{};
};
