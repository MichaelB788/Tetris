#ifndef TETRIS_HPP
#define TETRIS_HPP
#include "Tetromino.hpp"
#include <array>
#include <vector>

class Tetris {
public:
  void move_left() { shift({.x = -1, .y = 0}); }

  void move_right() { shift({.x = 1, .y = 0}); }

  void move_down() {
    if (!mechanics::try_shift(current_, matrix_, {.x = 0, .y = 1}))
      spawn_next();
  }

  void drop() {
    mechanics::drop(current_, matrix_);
    spawn_next();
  }

  void hold();

  void rotate_clockwise() { rotate(rs_.clockwise); }

  void rotate_counterclockwise() { rotate(rs_.counterclockwise); }

  void reset();

public:
  Tetromino::Projection current() const { return current_.projection(); }

  Tetromino::Projection ghost() const { return ghost_.projection(); }

  const Matrix &matrix() const { return matrix_; }

  const std::optional<Tetromino> &optional_hold() const { return hold_; }

  const NextQueue &next_queue() const { return next_queue_; }

  unsigned score() const { return score_; }

  unsigned high_score() const { return high_score_; }

private:
  using Matrix = std::array<std::array<Tetromino::Type, 10>, 20>;

  void update_ghost() {
    ghost_ = current_;
    mechanics::drop(ghost_, matrix_);
  }

  void set_current(const Tetromino &other) {
    current_ = other;
    current_.set_pos(Tetromino::INIT_POS);
    update_ghost();
  }

  void shift(Point delta) {
    mechanics::try_shift(current_, matrix_, delta);
    update_ghost();
  }

  void rotate(mechanics::RotationFunc rotation_func) {
    rotation_func(current_, matrix_);
    update_ghost();
  }

  void reset_current();

  void spawn_next();

  Matrix mat{};

  Tetromino current_{}, ghost_{}, hold_{};

  std::vector<Tetromino> next_queue_(5);

  bool hold_triggered = false, has_hold = false;

  unsigned lines_cleared{};
};

#endif
