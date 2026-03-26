#include "Tetris.hpp"
#include <algorithm>
#include <ranges>

namespace {
[[nodiscard]] bool point_out_of_bounds(Point p) {
  return Matrix::out_of_bounds(p.x, p.y);
};

Tetromino pop_next(std::deque<Tetromino> &queue) {
  Tetromino ret = queue.front();
  queue.pop_front();
  queue.push_back(Tetromino::random_piece());
  return ret;
}
} // namespace

Tetris::Tetris() {
  next_queue_.resize(4);
  for (int i = 0; i < 4; ++i)
    next_queue_.push_back(Tetromino::random_piece());
}

void Tetris::hold() {
  if (hold_triggered_)
    return;

  if (hold_present_) {
    const Tetromino temp = Tetromino(hold_.type());
    hold_ = current_;
    current_ = temp;
  } else {
    hold_ = current_;
    current_ = pop_next(next_queue_);
  }

  hold_triggered_ = true;
}

void Tetris::reset() {
  cleared_ = 0;
  matrix_.clear();
  current_ = pop_next(next_queue_);
  game_over_ = hold_present_ = hold_triggered_ = false;
}

void Tetris::lock_piece() {
  for (auto &pos : current_.shape()) {
    matrix_(pos.x, pos.y) = static_cast<Matrix::Cell>(current_.type());
  }
  cleared_ += matrix_.clear_lines();
}

void Tetris::spawn_next() {
  const auto hits_ground = [this](Point p) {
    return Matrix::is_ground(matrix_(p.x, p.y));
  };

  current_ = pop_next(next_queue_);

  while (std::ranges::any_of(current_.shape(), hits_ground)) {
    current_.shift({0, -1});

    if (std::ranges::any_of(current_.shape(), point_out_of_bounds)) {
      game_over_ = true;
      return;
    }
  }
}

bool Tetris::shift_current(Point delta) {
  const auto is_invalid = [this](Point p) {
    return Matrix::out_of_bounds(p.x, p.y) &&
           Matrix::is_ground(matrix_(p.x, p.y));
  };

  auto shifted = current_.shape() |
                 std::views::transform([&](Point p) { return p + delta; });

  if (std::ranges::none_of(shifted, is_invalid)) {
    current_.shift(delta);
    return true;
  }

  return false;
}
