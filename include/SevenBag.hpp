#pragma once
#include "Tetromino.hpp"
#include <array>
#include <cstddef>
#include <random>

class SevenBag {
public:
  explicit SevenBag(std::mt19937 &rng);

  void shuffle(std::mt19937 &rng);

  auto pop(std::mt19937 &rng) -> Tetromino::Type;

  using Preview = std::array<Tetromino::Type, 4>;
  auto preview() const -> Preview;

  auto peek() const -> Tetromino;

private:
  size_t read_ = 0;

  std::array<Tetromino::Type, 7> curr_bag_{
      Tetromino::Type::I, Tetromino::Type::O, Tetromino::Type::T,
      Tetromino::Type::S, Tetromino::Type::Z, Tetromino::Type::J,
      Tetromino::Type::L};

  std::array<Tetromino::Type, 7> next_bag_{
      Tetromino::Type::I, Tetromino::Type::O, Tetromino::Type::T,
      Tetromino::Type::S, Tetromino::Type::Z, Tetromino::Type::J,
      Tetromino::Type::L};
};
