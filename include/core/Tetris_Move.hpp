#pragma once
#include "util/Point.hpp"

struct Tetromino;
class Matrix;

namespace tetris::move {
auto shift(Tetromino &piece, const Matrix &matrix, Point delta) -> bool;

void hard_drop(Tetromino &piece, const Matrix &matrix);
} // namespace tetris::move

enum class RotationDir { Clockwise, CounterClockwise, HalfTurn };
namespace tetris::srs {
void rotation(Tetromino &tet, const Matrix &matrix, RotationDir dir);
} // namespace tetris::srs
