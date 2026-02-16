#ifndef TETRIS_MECHANICS_HPP
#define TETRIS_MECHANICS_HPP
#include "Tetromino.hpp"

class Matrix;

namespace mechanics {
void place(Tetromino::Projection tet, Matrix &matrix);

[[nodiscard]] bool can_place(Tetromino::Projection tet, const Matrix &matrix);

[[nodiscard]] bool is_within_bounds(Tetromino::Projection tet);

bool try_shift(Tetromino &tet, const Matrix &matrix, Point delta);

bool try_spawn(Tetromino &tet, const Tetromino &new_tet, const Matrix &matrix);

void drop(Tetromino &tet, const Matrix &matrix);

using RotationFunc = void (*)(Tetromino &tet, const Matrix &matrix);

struct RotationSystem {
  RotationFunc clockwise;
  RotationFunc counterclockwise;
};

namespace srs {
void clockwise_rotation(Tetromino &tet, const Matrix &matrix);

void counterclockwise_rotation(Tetromino &tet, const Matrix &matrix);

inline constexpr RotationSystem srs{clockwise_rotation,
                                    counterclockwise_rotation};
} // namespace srs
} // namespace mechanics

#endif
