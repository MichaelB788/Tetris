#pragma once
#include "Matrix.hpp"
#include "Tetromino.hpp"
#include <deque>

class Tetris {
public:
  Tetris();

  void move_left() { shift_current({-1, 0}); }

  void move_right() { shift_current({1, 0}); }

  void move_down() {
    if (!shift_current({0, 1}))
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
  [[nodiscard]] const Tetromino &current() const { return current_; }

  [[nodiscard]] const Matrix &matrix() const { return matrix_; }

  [[nodiscard]] const Tetromino &optional_hold() const { return hold_; }

  [[nodiscard]] const std::deque<Tetromino> &next_queue() const {
    return next_queue_;
  }

  [[nodiscard]] int score() const { return cleared_; }

private:
  bool shift_current(Point delta);

private:
  void lock_piece();

  void spawn_next();

private:
  Matrix matrix_{};

  Tetromino current_{}, hold_{};

  std::deque<Tetromino> next_queue_{};

  bool hold_triggered_ = false, hold_present_ = false, game_over_ = false;

  unsigned cleared_ = 0;
};
