#pragma once
#include "core/Tetromino.hpp"
#include <array>
#include <cstddef>
#include <random>

class SevenBag {
public:
  SevenBag(std::mt19937 &rng);

  void shuffle(std::mt19937 &rng);

  auto pop(std::mt19937 &rng) -> Tetromino;

  using Preview = std::array<Tetromino::Type, 4>;
  auto preview() const -> Preview;

  auto peek() const -> Tetromino { return Tetromino{.type = curr_bag_[read_]}; }

private:
  size_t read_ = 0;
  std::array<Tetromino::Type, 7> curr_bag_{
      Tetromino::I, Tetromino::O, Tetromino::T, Tetromino::S,
      Tetromino::Z, Tetromino::J, Tetromino::L};
  std::array<Tetromino::Type, 7> next_bag_{
      Tetromino::I, Tetromino::O, Tetromino::T, Tetromino::S,
      Tetromino::Z, Tetromino::J, Tetromino::L};
};
