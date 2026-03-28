#pragma once
#include "CircularBuffer.hpp"
#include "Tetromino.hpp"

class NextQueue {
public:
  NextQueue() { shuffle(); }

  [[nodiscard]] Tetromino::Type pop();

  void shuffle();

private:
  void push_random();

private:
  CircularBuffer<Tetromino::Type, 4> queue_{};
};
