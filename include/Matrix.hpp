#pragma once
#include "FPoint.hpp"
#include "Piece.hpp"
#include <array>
#include <optional>

class Matrix {
public:
  static constexpr size_t ROWS = 24;
  static constexpr size_t COLS = 10;

  void clear_all();
  [[nodiscard]] auto clear_lines() -> unsigned;

  [[nodiscard]] static auto is_fpos_within_bounds(FPoint pos) -> bool;
  [[nodiscard]] auto is_fpos_valid_at(FPoint pos) const -> bool;

  [[nodiscard]] auto at(FPoint pos) -> std::optional<Piece::Type> &;
  [[nodiscard]] auto at(FPoint pos) const -> std::optional<Piece::Type>;

private:
  std::array<std::array<std::optional<Piece::Type>, COLS>, ROWS> data{};
};
