#include "core/Playfield.hpp"
#include "core/NextQueue.hpp"
#include "util/Point.hpp"
#include <optional>

bool Playfield::shift_player(Point delta) {
  bool success = matrix_.is_move_valid(player_.test_shift(delta));
  if (success) {
    player_.shift(delta);
  }
  return success;
}

int Playfield::lock_and_get_points() {
  matrix_.place(player_);
  return matrix_.clear_lines();
};

bool Playfield::swap_with_held(std::optional<Tetromino::Type> &held) {
  Tetromino::Type new_hold = player_.type();
  if (held.has_value()) {
    player_ = Tetromino(held.value(), INIT_POS);
    held = new_hold;
    return true;
  } else {
    held = new_hold;
    return false;
  }
}

bool Playfield::switch_to_next(NextQueue &next) {
  Tetromino next_piece = Tetromino(next.pop(), INIT_POS);

  for (int i = 0; i < 5; ++i) {
    if (matrix_.is_move_valid(next_piece.shape())) {
      player_ = next_piece;
      return true;
    } else {
      next_piece.shift(Point::up());
    }
  }

  return false;
}

Point Playfield::compute_drop_distance() const {
  Point delta = {0, 0};
  while (matrix_.is_move_valid(player_.test_shift(delta + Point{0, 1}))) {
    delta += {0, 1};
  }
  return delta;
}

Tetromino Playfield::ghost() const {
  Tetromino ghost = player_;
  ghost.shift(compute_drop_distance());
  return ghost;
}
