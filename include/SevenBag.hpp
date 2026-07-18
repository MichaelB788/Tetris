#pragma once
#include "Tetromino.hpp"
#include <array>
#include <cstddef>
#include <random>

class SevenBag {
public:
  using Preview = std::array<Tetromino::Type, 4>;

  explicit SevenBag(std::mt19937 &rng);

  void shuffle();
  [[nodiscard]] auto pop() -> Tetromino::Type;
  [[nodiscard]] auto peek() const -> Tetromino::Type;
  [[nodiscard]] auto get_preview() const -> Preview;

private:
  std::mt19937 &rng;

  size_t read = 0;
  std::array<Tetromino::Type, 7> curr_bag{};
  std::array<Tetromino::Type, 7> next_bag{};
};
