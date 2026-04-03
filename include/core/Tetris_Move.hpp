#pragma once
#include "Matrix.hpp"
#include "Tetromino.hpp"

namespace tetris::move {
auto shift(Tetromino &piece, const Matrix &matrix, Point delta) -> bool;

[[nodiscard]] auto compute_dropped(const Tetromino &piece, const Matrix &matrix)
    -> Tetromino;
} // namespace tetris::move

enum class RotationDir { CW, CCW };
namespace tetris::srs {
void rotation(Tetromino &tet, const Matrix &matrix, RotationDir dir);
} // namespace tetris::srs
