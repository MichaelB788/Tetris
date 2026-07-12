#include "Tetris.hpp"
#include "Tetromino.hpp"
#include <chrono>
#include <random>

static constexpr Point INIT_POS = {.x = 4, .y = 4};

Tetris::Tetris(std::mt19937 &rng)
    : seven_bag_(rng), active_piece_(seven_bag_.pop(rng), INIT_POS) {}

void Tetris::invoke_action(Command action, std::mt19937 &rng) {
  switch (action) {
    using enum Command;
  case MoveLeft:
    active_piece_.local_shift({.x = -1}, matrix_);
    break;
  case MoveRight:
    active_piece_.local_shift({.x = 1}, matrix_);
    break;
  case SoftDrop:
    active_piece_.local_shift({.y = 1}, matrix_);
    break;
  case HardDrop:
    active_piece_.hard_drop(matrix_);
    complete_move(rng);
    break;
  case RotateClockwise:
    active_piece_.srs_rotate_cw(matrix_);
    break;
  case RotateCounterclockwise:
    active_piece_.srs_rotate_ccw(matrix_);
    break;
  case RotateHalf:
    active_piece_.srs_rotate_half(matrix_);
    break;
  case Hold:
    hold(rng);
    break;
  }
}

void Tetris::tick(std::chrono::nanoseconds delta_time, std::mt19937 &rng) {
  gravity_delay_.invoke_periodically(
      delta_time, [this] { active_piece_.local_shift({.y = 1}, matrix_); });

  if (!matrix_.is_move_valid(active_piece_.get_shifted_shape({.y = 1}))) {
    lock_delay_.invoke_periodically(delta_time, [&] { complete_move(rng); });
  }
}

auto Tetris::ghost_piece() const -> Tetromino {
  return Tetromino(active_piece_.get_type(),
                   active_piece_.get_pos_after_hard_drop(matrix_),
                   active_piece_.get_rotation());
}

void Tetris::hold(std::mt19937 &rng) {
  if (!hold_command_triggered_) {
    hold_command_triggered_ = true;
    const auto to_hold = active_piece_.get_type();
    attempt_swap(Tetromino(held_piece_.has_value() ? held_piece_.value()
                                                   : seven_bag_.pop(rng)));
    held_piece_ = to_hold;
    lock_delay_.reset();
  }
}

auto Tetris::attempt_swap(Tetromino next) -> bool {
  active_piece_ = next;
  auto new_pos = INIT_POS;
  for (int i = 0; i < (MATRIX_ROWS - INIT_POS.y); ++i) {
    if (matrix_.is_move_valid(active_piece_.get_shifted_shape(new_pos))) {
      active_piece_.set_pos(new_pos);
      return true;
    } else {
      --new_pos.y;
    }
  }
  return false;
}

void Tetris::complete_move(std::mt19937 &rng) {
  // Place Tetromino and update scores
  matrix_.lock_down(active_piece_);
  score_ += matrix_.clear_lines();

  // Update the gravity rate
  {
    using namespace std::chrono_literals;
    static constexpr std::array LEVELS{1000ms, 900ms, 800ms, 700ms,
                                       600ms,  500ms, 450ms, 400ms,
                                       300ms,  200ms, 100ms};

    gravity_delay_.set_duration(score_ < 100 ? LEVELS[score_ / 10]
                                             : LEVELS.back());
  }

  if (attempt_swap(Tetromino(seven_bag_.pop(rng)))) {
    hold_command_triggered_ = false;
    lock_delay_.reset();
  } else {
    game_over_ = true;
  }
}
