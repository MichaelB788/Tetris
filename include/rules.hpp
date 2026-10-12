#pragma once
#include "Matrix.hpp"
#include "Piece.hpp"
#include <optional>

namespace piece_query {
[[nodiscard]] auto is_valid_shape(const Piece::Shape &shape,
                                  const Matrix &matrix) -> bool;

[[nodiscard]] auto is_shape_within_bounds(const Piece::Shape &shape) -> bool;
} // namespace piece_query

namespace piece_action {
[[nodiscard]] auto hard_drop(Piece pc, const Matrix &matrix) -> Piece;

[[nodiscard]] auto shift(Piece pc, FPoint delta, const Matrix &matrix)
    -> std::optional<Piece>;

[[nodiscard]] auto srs_rotation(Piece pc, Piece::Rotation dir,
                                const Matrix &matrix) -> std::optional<Piece>;

void lock_down(Piece pc, Matrix &matrix);
} // namespace piece_action
