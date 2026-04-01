#pragma once
#include "core/Matrix.hpp"
#include "core/NextQueue.hpp"
#include "core/Tetromino.hpp"
#include "core/srs.hpp"
#include <optional>

class Playfield {
public:
  bool shift_player(Point delta);

  void rotate_player_cw() { srs::rotate_cw(player_, matrix_); }

  void rotate_player_ccw() { srs::rotate_ccw(player_, matrix_); }

  void reset(Tetromino::Type new_type) {
    matrix_.clear();
    player_ = Tetromino(new_type, INIT_POS);
  }

  int lock_and_get_points();

  bool swap_with_held(std::optional<Tetromino::Type> &held);

  bool switch_to_next(NextQueue &next_queue);

  [[nodiscard]] Point compute_drop_distance() const;

  [[nodiscard]] Tetromino ghost() const;

  [[nodiscard]] const Matrix &matrix() const { return matrix_; }

  [[nodiscard]] const Tetromino &player() const { return player_; }

private:
  static constexpr Point INIT_POS = {5, 2};

  Matrix matrix_{};

  Tetromino player_{};
};
