#pragma once
#include "core/Tetromino.hpp"
#include <cstddef>
#include <random>

class NextQueue {
public:
  void shuffle(std::mt19937 &rng);

  auto pop(std::mt19937 &rng) -> Tetromino;

  auto peek() const -> Tetromino { return Tetromino{.type = buffer_[read_]}; }

private:
  std::array<Tetromino::Type, 7> buffer_{
      Tetromino::I, Tetromino::O, Tetromino::T, Tetromino::S,
      Tetromino::Z, Tetromino::J, Tetromino::L};
  size_t read_ = 0;
};
