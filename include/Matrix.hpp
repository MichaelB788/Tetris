#pragma once
#include "Piece.hpp"
#include "Point.hpp"
#include <array>
#include <cstddef>
#include <optional>

class Matrix {
public:
  static constexpr size_t ROWS = 24;
  static constexpr size_t COLS = 10;

  [[nodiscard]] auto at(size_t x, size_t y) const -> std::optional<Piece::Type>;
  [[nodiscard]] auto at(FPoint pos) const -> std::optional<Piece::Type>;

  void lock_down(Piece piece);
  auto clear_lines() -> unsigned;
  void clear();

  [[nodiscard]] auto can_place(const Piece::Shape &shape) const -> bool;

private:
  std::array<std::array<std::optional<Piece::Type>, COLS>, ROWS> data{};
};

namespace matrix {
[[nodiscard]] auto is_piece_within_bounds(const Piece::Shape &piece) -> bool;
}
