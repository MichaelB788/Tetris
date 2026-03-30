#pragma once
#include "Matrix.hpp"
#include "Tetromino.hpp"
#include "srs.hpp"

class Playfield {
public:
  bool shift_player(Point delta);

  void rotate_player_cw() { srs::rotate_cw(player_, matrix_); }

  void rotate_player_ccw() { srs::rotate_ccw(player_, matrix_); }

  void reset(Tetromino::Type new_type) {
    matrix_.clear();
    player_ = Tetromino(new_type, INIT_POS);
  }

  int lock_and_get_points() {
    matrix_.place(player_);
    return matrix_.clear_lines();
  };

  void set_player_unchecked(Tetromino::Type new_type) {
    player_ = Tetromino{new_type, INIT_POS};
  }

  [[nodiscard]] bool set_player(Tetromino::Type new_type);

  [[nodiscard]] Point compute_drop_distance() const;

  [[nodiscard]] Tetromino ghost() const {
    Tetromino ghost = player_;
    ghost.shift(compute_drop_distance());
    return ghost;
  }

  [[nodiscard]] const Matrix &matrix() const { return matrix_; }

  [[nodiscard]] const Tetromino &player() const { return player_; }

private:
  static constexpr Point INIT_POS = {5, 2};

  Matrix matrix_{};

  Tetromino player_{};
};
