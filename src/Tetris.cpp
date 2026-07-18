#include "Tetris.hpp"
#include "Point.hpp"
#include "Tetromino.hpp"
#include <chrono>
#include <optional>

void Tetris::move_left() { move_active({.x = -1}); }

void Tetris::move_right() { move_active({.x = 1}); }

void Tetris::soft_drop() { lock_delay_.begin_timer_if(!move_active({.y = 1})); }

void Tetris::hard_drop() {
  active_piece_.hard_drop(matrix_);
  finalize_move();
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

void Tetris::hold_active() {
  if (hold_command_triggered_) {
    return;
  }

  const auto to_hold = active_piece_.get_type();
  if (try_spawn_next(held_piece_.has_value() ? held_piece_.value()
                                             : seven_bag_.pop(rng_))) {
    hold_command_triggered_ = true;
    held_piece_ = to_hold;
  } else {
    state_ = State::GameOver;
  }
}

void Tetris::pause() {
  if (state_ == State::Running) {
    state_ = State::Paused;
  }
}

void Tetris::unpause() {
  if (state_ == State::Paused) {
    state_ = State::Running;
  }
}

void Tetris::tick(std::chrono::nanoseconds delta_time) {
  gravity_delay_.invoke_periodically(delta_time, [this] {
    lock_delay_.begin_timer_if(!active_piece_.try_shift({.y = 1}, matrix_));
  });

  lock_delay_.tick(delta_time, [this] {
    if (!matrix_.is_move_valid(active_piece_.get_shifted_shape({.y = 1}))) {
      finalize_move();
    }
  });
}

void Tetris::reset() {
  state_ = State::Running;
  score_ = 0;
  hold_command_triggered_ = false;

  gravity_delay_.reset();
  lock_delay_.reset();

  held_piece_ = std::nullopt;
  matrix_.clear();
  seven_bag_.shuffle(rng_);
  active_piece_ = {seven_bag_.pop(rng_), SPAWN_POINT};
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

auto Tetris::move_active(Point<int> delta) -> bool {
  const auto has_shifted = active_piece_.try_shift(delta, matrix_);
  lock_delay_.perform_lock_reset_if(has_shifted);
  return has_shifted;
}

auto Tetris::rotate_active(Tetromino::Rotation next) -> bool {
  const auto has_rotated = active_piece_.srs_rotation(next, matrix_);
  lock_delay_.perform_lock_reset_if(has_rotated);
  return has_rotated;
}

auto Tetris::try_spawn_next(Tetromino::Type next) -> bool {
  active_piece_ = {next, SPAWN_POINT};

  auto was_successful_turn = true;
  while (matrix_.is_shape_hitting_ground(active_piece_.get_shape())) {
    active_piece_.shift({.y = -1});
    was_successful_turn = matrix_.is_move_valid(active_piece_.get_shape());
  }

  if (was_successful_turn) {
    lock_delay_.reset();
    gravity_delay_.reset();
  }

  return was_successful_turn;
}

void Tetris::update_level() {
  using namespace std::chrono_literals;
  static constexpr std::array LEVELS{1000ms, 900ms, 800ms, 700ms, 600ms, 500ms,
                                     450ms,  400ms, 300ms, 200ms, 100ms};

  gravity_delay_.set_duration(score_ < 100 ? LEVELS[score_ / 10]
                                           : LEVELS.back());
}

void Tetris::finalize_move() {
  matrix_.lock_down(active_piece_);
  score_ += matrix_.clear_lines();

  update_level();

  if (try_spawn_next(seven_bag_.pop(rng_))) {
    hold_command_triggered_ = false;
  } else {
    state_ = State::GameOver;
  }
}
