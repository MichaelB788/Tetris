#pragma once
#include "Matrix.hpp"
#include "Piece.hpp"
#include <optional>

namespace piece_action {
[[nodiscard]] auto hard_drop(Piece pc, const Matrix &matrix) -> Piece;

[[nodiscard]] auto shift(Piece pc, FPoint delta, const Matrix &matrix)
    -> std::optional<Piece>;

[[nodiscard]] auto srs_rotation(Piece pc, Piece::Rotation next,
                                const Matrix &matrix) -> std::optional<Piece>;
} // namespace piece_action
