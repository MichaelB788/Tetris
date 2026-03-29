#include "Tetris.hpp"
#include <algorithm>
#include <ranges>

void Tetris::drop() {
  bool can_shift;
  do {
    can_shift = shift_current({0, 1});
  } while (can_shift);
  shift_current({0, -1});
  spawn_next();
}

void Tetris::hold() {
  if (hold_triggered_)
    return;

  if (hold_present_) {
    const Tetromino temp = Tetromino(hold_.type());
    hold_ = player_;
    player_ = temp;
  } else {
    hold_ = player_;
    player_ = pop_next(queue_);
  }

  hold_triggered_ = true;
}

void Tetris::reset() {
  score_ = 0;
  matrix_.clear();
  player_ = pop_next(queue_);
  game_over_ = hold_present_ = hold_triggered_ = false;
}

void Tetris::lock_piece() {
  for (auto &pos : player_) {
    matrix_(pos.x, pos.y) = static_cast<Matrix::Cell>(player_.type());
  }
  score_ += matrix_.clear_lines();
}

void Tetris::spawn_next() {
  const auto hits_ground = [this](Point p) {
    return Matrix::is_ground(matrix_(p.x, p.y));
  };

  lock_piece();
  player_ = pop_next(queue_);

  while (std::ranges::any_of(player_, hits_ground)) {
    player_.shift({0, -1});

    if (std::ranges::any_of(player_, point_out_of_bounds)) {
      game_over_ = true;
      return;
    }
  }
}

bool Tetris::shift_current(Point delta) {
  const auto is_valid = [&](Point p) { return matrix_.is_valid(p.x, p.y); };

  auto shifted =
      player_ | std::views::transform([&](Point p) { return p + delta; });

  if (std::ranges::all_of(shifted, is_valid)) {
    player_.shift(delta);
    return true;
  }

  return false;
}
