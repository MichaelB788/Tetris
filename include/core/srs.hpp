#pragma once

class Tetromino;
class Matrix;

namespace srs {
void rotate_cw(Tetromino &tet, const Matrix &matrix);

void rotate_ccw(Tetromino &tet, const Matrix &matrix);
} // namespace srs
