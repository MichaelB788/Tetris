#pragma once
#include "Matrix.hpp"
#include "Tetromino.hpp"
#include "srs.hpp"

class Playfield {
public:
  Playfield(Tetromino::Type init_type) : player_(init_type, INIT_POS) {}

  void shift_player(Point delta) {
    if (can_shift_player(delta))
      player_.shift(delta);
  }

  void shift_player_unchecked(Point delta) { player_.shift(delta); }

  void rotate_piece_cw() { srs::rotate_cw(player_, matrix_); }

  void rotate_piece_ccw() { srs::rotate_ccw(player_, matrix_); }

  void lock_piece();

  void set_player_piece(const Tetromino &new_piece) { player_ = new_piece; }

  void set_player_type(Tetromino::Type new_type) {
    player_ = {new_type, INIT_POS};
  }

  [[nodiscard]] Tetromino compute_drop() const;

  [[nodiscard]] bool can_shift_player(Point delta) const;

  [[nodiscard]] const Matrix &matrix() const { return matrix_; }

  [[nodiscard]] const Tetromino &player() const { return player_; }

private:
  static constexpr Point INIT_POS = {5, 2};

  Matrix matrix_{};

  Tetromino player_{};
};
