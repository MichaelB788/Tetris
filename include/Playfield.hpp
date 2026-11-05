#pragma once
#include "Geometry.hpp"
#include "Piece.hpp"
#include <array>
#include <cstddef>
#include <optional>

class Playfield {
public:
  using Cell = std::optional<Piece::Type>;

  static constexpr size_t ROWS = 24;
  static constexpr size_t COLS = 10;
  static constexpr Rectangle BOUNDS = {0, 0, COLS - 1, ROWS - 1};

  void clear_all_rows();
  // returns the number of rows cleared
  auto clear_full_rows() -> unsigned;

  void lock_down(const Piece &piece);

  [[nodiscard]] static auto is_within_bounds(const Piece::Shape &shape) -> bool;
  [[nodiscard]] auto can_place(const Piece::Shape &shape) const -> bool;

  [[nodiscard]] auto at(Point pos) const -> Cell;
  [[nodiscard]] auto operator()(size_t x, size_t y) const -> Cell;

private:
  std::array<std::array<Cell, COLS>, ROWS> cells{};
};
