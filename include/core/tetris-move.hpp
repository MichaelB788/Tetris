#pragma once
#include "Matrix.hpp"
#include "Tetromino.hpp"

namespace tetris::move {
bool shift_piece(Tetromino &piece, const Matrix &matrix, Point delta);

[[nodiscard]] Tetromino compute_dropped(const Tetromino &piece,
                                        const Matrix &matrix);
} // namespace tetris::move

namespace tetris::srs {
void rotate_cw(Tetromino &tet, const Matrix &matrix);

void rotate_ccw(Tetromino &tet, const Matrix &matrix);
} // namespace tetris::srs
