#pragma once
#include "util/Point.hpp"

struct Tetromino;
class Matrix;

namespace tetris::move {
auto shift(Tetromino &piece, const Matrix &matrix, Point delta) -> bool;

[[nodiscard]] auto hard_drop_delta(const Tetromino &piece, const Matrix &matrix)
    -> Point;

[[nodiscard]] auto hard_dropped(const Tetromino &piece, const Matrix &matrix)
    -> Tetromino;
} // namespace tetris::move

enum class RotationDir { Clockwise, CounterClockwise, HalfTurn };
namespace tetris::srs {
void rotation(Tetromino &tet, const Matrix &matrix, RotationDir dir);
} // namespace tetris::srs
