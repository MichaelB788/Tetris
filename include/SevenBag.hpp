#pragma once
#include "Piece.hpp"
#include <array>
#include <cstddef>
#include <random>

class SevenBag {
public:
  using Preview = std::array<Piece::Type, 4>;

  SevenBag(std::mt19937 &rng);

  [[nodiscard]] auto pop_next_type() -> Piece::Type;

  [[nodiscard]] auto get_preview() const -> Preview;

  void shuffle();

private:
  size_t read_idx{};

  std::array<Piece::Type, 7> current{};
  std::array<Piece::Type, 7> next{
      Piece::Type::I, Piece::Type::O, Piece::Type::T, Piece::Type::S,
      Piece::Type::Z, Piece::Type::J, Piece::Type::L};

  std::mt19937 &rng;
};
