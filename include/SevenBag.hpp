#pragma once
#include "Piece.hpp"
#include <array>
#include <cstddef>
#include <random>

class SevenBag {
public:
  using Preview = std::array<Piece::Type, 4>;

  explicit SevenBag(std::mt19937 &rng);

  void shuffle();
  [[nodiscard]] auto pop() -> Piece::Type;
  [[nodiscard]] auto peek() const -> Piece::Type;
  [[nodiscard]] auto get_preview() const -> Preview;

private:
  std::mt19937 &rng;

  size_t read = 0;
  std::array<Piece::Type, 7> curr_bag{};
  std::array<Piece::Type, 7> next_bag{};
};
