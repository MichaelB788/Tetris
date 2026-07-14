#include "Tetris.hpp"
#include "Point.hpp"
#include "Tetromino.hpp"
#include <chrono>
#include <optional>
#include <random>

void Tetris::move_left() { shift_active({.x = -1}); }

void Tetris::move_right() { shift_active({.x = 1}); }

void Tetris::soft_drop() { shift_active({.y = 1}); }

void Tetris::hard_drop(std::mt19937 &rng) {
  active_piece_.hard_drop(matrix_);
  continue_to_next_turn(rng);
}

void Tetris::rotate_cw() {
  rotate_active(tetromino::rotated_cw(active_piece_.get_rotation(), 1));
}

void Tetris::rotate_ccw() {
  rotate_active(tetromino::rotated_cw(active_piece_.get_rotation(), 3));
}

void Tetris::rotate_half() {
  rotate_active(tetromino::rotated_cw(active_piece_.get_rotation(), 2));
}

void Tetris::hold_active(std::mt19937 &rng) {
  if (hold_command_triggered_) {
    return;
  }

  const auto to_hold = active_piece_.get_type();
  if (try_spawn_next(held_piece_.has_value() ? held_piece_.value()
                                             : seven_bag_.pop(rng))) {
    hold_command_triggered_ = true;
    held_piece_ = to_hold;
  } else {
    state_ = State::GameOver;
  }
}

void Tetris::toggle_pause() {
  if (state_ == State::Running) {
    state_ = State::Paused;
  } else if (state_ == State::Paused) {
    state_ = State::Running;
  }
}

void Tetris::tick(std::chrono::nanoseconds delta_time, std::mt19937 &rng) {
  lock_delay_.invoke_periodically(delta_time, [this] { lock_pending_ = true; });

  gravity_delay_.invoke_periodically(delta_time, [&] {
    if (active_piece_.try_shift({.y = 1}, matrix_)) {
      lock_delay_.reset();
    } else if (lock_pending_) {
      continue_to_next_turn(rng);
    }
  });
}

void Tetris::reset(std::mt19937 &rng) {
  state_ = State::Running;
  score_ = 0;
  hold_command_triggered_ = false;

  lock_delay_.reset();
  gravity_delay_.reset();

  held_piece_ = std::nullopt;
  matrix_.clear();
  seven_bag_.shuffle(rng);
  active_piece_ = {seven_bag_.pop(rng), INIT_POS};
}

auto Tetris::get_state() const -> State { return state_; }

auto Tetris::get_score() const -> unsigned { return score_; }

auto Tetris::get_matrix() const -> const Matrix & { return matrix_; }

auto Tetris::get_active_piece() const -> Tetromino { return active_piece_; }

auto Tetris::get_seven_bag() const -> SevenBag::Preview {
  return seven_bag_.preview();
}

auto Tetris::get_held_piece() const -> std::optional<Tetromino::Type> {
  return held_piece_;
}

auto Tetris::get_ghost_piece() const -> Tetromino {
  return {active_piece_.get_type(),
          active_piece_.get_pos_after_hard_drop(matrix_),
          active_piece_.get_rotation()};
}

void Tetris::shift_active(Point<int> delta) {
  if (active_piece_.try_shift(delta, matrix_)) {
    if (lock_resets_ < lock_reset_limit_) {
      ++lock_resets_;
      lock_delay_.reset();
    }
  }
}

void Tetris::rotate_active(Tetromino::Rotation next) {
  if (active_piece_.srs_rotation(next, matrix_)) {
    if (lock_resets_ < lock_reset_limit_) {
      ++lock_resets_;
      lock_delay_.reset();
    }
  }
}

auto Tetris::try_spawn_next(Tetromino::Type next) -> bool {
  active_piece_ = {next, INIT_POS};
  bool success = true;
  while (matrix_.is_shape_hitting_ground(active_piece_.get_shape())) {
    active_piece_.shift({.y = -1});
    success = matrix_.is_move_valid(active_piece_.get_shape());
  }

  if (!success) {
    lock_resets_ = 0;
    lock_pending_ = false;
    lock_delay_.reset();
    gravity_delay_.reset();
  }
  return success;
}

void Tetris::update_level() {
  using namespace std::chrono_literals;
  static constexpr std::array LEVELS{1000ms, 900ms, 800ms, 700ms, 600ms, 500ms,
                                     450ms,  400ms, 300ms, 200ms, 100ms};

  gravity_delay_.set_duration(score_ < 100 ? LEVELS[score_ / 10]
                                           : LEVELS.back());
  lock_delay_.set_duration(gravity_delay_.duration() * 2);
}

void Tetris::continue_to_next_turn(std::mt19937 &rng) {
  matrix_.lock_down(active_piece_);
  score_ += matrix_.clear_lines();
  update_level();

  if (try_spawn_next(seven_bag_.pop(rng))) {
    hold_command_triggered_ = false;
  } else {
    state_ = State::GameOver;
  }
}
