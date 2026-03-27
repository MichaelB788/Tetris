#pragma once

class Tetromino;
class Matrix;

namespace srs {
void clockwise_rotation(Tetromino &tet, const Matrix &matrix);

void counterclockwise_rotation(Tetromino &tet, const Matrix &matrix);
} // namespace srs
