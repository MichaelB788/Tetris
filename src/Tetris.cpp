#include "Tetris.hpp"
#include <algorithm>
#include <ranges>

namespace {
[[nodiscard]] bool point_out_of_bounds(Point p) {
  return Matrix::out_of_bounds(p.x, p.y);
};
} // namespace

Tetris::Tetris() {
  next_queue_.resize(4);
  for (int i = 0; i < 4; ++i)
    next_queue_.push_back(Tetromino::rand());
}

/*
void Tetris::hold() {
  if (hold_command_triggered_)
    return;

  reset_current();
  if (hold_.has_value()) {
    const Tetromino temp = hold_.value();
    hold_ = current_;
    set_current(temp);
  } else {
    hold_ = current_;
    set_current(next_queue_.pop_next());
  }

  hold_command_triggered_ = true;
}

void Tetris::reset() {
  score_ = 0;
  state_ = State::Running;
  matrix_.clear();
  set_current(next_queue_.pop_next());
  hold_ = std::nullopt;
  hold_command_triggered_ = false;
}

void Tetris::reset_current() {
  current_.set_pos({.x = 0, .y = 0});
  while (current_.curr_rotation() != 0)
    current_.rotate_clockwise();
}
*/
Tetromino pop_next(std::deque<Tetromino> &queue) {
  Tetromino ret = queue.front();
  queue.pop_front();
  queue.push_back(Tetromino::rand());
  return ret;
}

void Tetris::spawn_next() {
  const auto hits_ground = [this](Point p) {
    return matrix_(p.x, p.y) != Matrix::Cell::EMPTY;
  };

  for (auto &pos : current_.shape()) {
    matrix_(pos.x, pos.y) = static_cast<Matrix::Cell>(current_.type());
  }
  cleared_ += matrix_.clear_lines();

  current_ = pop_next(next_queue_);

  while (std::ranges::any_of(current_.shape(), hits_ground)) {
    current_.shift({0, -1});
    if (std::ranges::any_of(current_.shape(), point_out_of_bounds)) {
      game_over = true;
      return;
    }
  }
}

bool Tetris::shift_current(Point delta) {
  const auto is_valid = [this](Point p) {
    return !Matrix::out_of_bounds(p.x, p.y) &&
           matrix_(p.x, p.y) == Matrix::Cell::EMPTY;
  };

  auto shifted = current_.shape() |
                 std::views::transform([&](Point p) { return p + delta; });

  if (std::ranges::all_of(shifted, is_valid)) {
    current_.shift(delta);
    return true;
  }

  return false;
}
