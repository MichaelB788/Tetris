#pragma once
#include "Playfield.hpp"
#include <algorithm>
#include <ranges>

Tetromino Playfield::compute_drop() const {
  Tetromino dropped = player_;
  do {
    dropped.shift({0, 1});
  } while (std::ranges::all_of(dropped.shape(), Matrix::IsPosValid(matrix_)));

  dropped.shift({0, -1});
  return dropped;
}

bool Playfield::can_shift_player(Point delta) const {
  auto shifted = player_.shape() |
                 std::views::transform([&](Point p) { return p + delta; });

  return std::ranges::all_of(shifted, Matrix::IsPosValid(matrix_));
}

void Playfield::lock_piece() {
  for (const auto &pos : player_.shape()) {
    matrix_.at(pos) = static_cast<Matrix::Cell>(player_.type());
  }
}
