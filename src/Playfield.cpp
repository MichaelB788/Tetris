#include "Playfield.hpp"
#include "Point.hpp"

bool Playfield::shift_player(Point delta) {
  bool success = matrix_.is_move_valid(player_.test_shift(delta));
  if (success) {
    player_.shift(delta);
  }
  return success;
}

bool Playfield::set_player(Tetromino::Type new_type) {
  Tetromino next = Tetromino(new_type, INIT_POS);

  // There's probably a better way of doing this.
  for (int i = 0; i < 5; ++i) {
    if (matrix_.is_move_valid(next.shape())) {
      player_ = next;
      return true;
    } else {
      next.shift({0, -1});
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
