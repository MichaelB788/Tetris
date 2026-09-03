#pragma once
#include "Constants.hpp"
#include "Point.hpp"
#include "Tetromino.hpp"
#include <array>
#include <optional>

class Matrix {
public:
  [[nodiscard]] auto at(size_t x, size_t y) const
      -> std::optional<Tetromino::Type>;
  [[nodiscard]] auto at(FPoint pos) const -> std::optional<Tetromino::Type>;

  void lock_down(Tetromino piece);
  auto clear_lines() -> unsigned;
  void clear();

  [[nodiscard]] static auto is_out_of_bounds(const Tetromino::Shape &shape)
      -> bool;
  [[nodiscard]] auto is_move_valid(const Tetromino::Shape &shape) const -> bool;

private:
  std::array<std::array<std::optional<Tetromino::Type>, MATRIX_COLS>,
             MATRIX_ROWS>
      data{};
};
