#pragma once
#include "Constants.hpp"
#include "Piece.hpp"
#include "Point.hpp"
#include <array>
#include <optional>

class Matrix {
public:
  [[nodiscard]] auto at(size_t x, size_t y) const -> std::optional<Piece::Type>;
  [[nodiscard]] auto at(FPoint pos) const -> std::optional<Piece::Type>;

  void lock_down(Piece piece);
  auto clear_lines() -> unsigned;
  void clear();

  [[nodiscard]] static auto is_out_of_bounds(const Piece::Shape &shape) -> bool;
  [[nodiscard]] auto can_place(const Piece::Shape &shape) const -> bool;

private:
  std::array<std::array<std::optional<Piece::Type>, MATRIX_COLS>, MATRIX_ROWS>
      data{};
};
