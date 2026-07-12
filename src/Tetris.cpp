#include "Tetris.hpp"
#include "Tetromino.hpp"
#include <chrono>
#include <random>

void Tetris::handle_command(Command command, std::mt19937 &rng) {
  switch (command) {
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
    continue_to_next_turn(rng);
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
    hold_active(rng);
    break;
  }
}

void Tetris::tick(std::chrono::nanoseconds delta_time, std::mt19937 &rng) {
  gravity_delay_.invoke_periodically(
      delta_time, [this] { active_piece_.local_shift({.y = 1}, matrix_); });

  if (!matrix_.is_move_valid(active_piece_.get_shifted_shape({.y = 1}))) {
    lock_delay_.invoke_periodically(delta_time,
                                    [&] { continue_to_next_turn(rng); });
  }
}

auto Tetris::get_state() const -> State { return state_; }

auto Tetris::get_score() const -> int { return score_; }

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

void Tetris::hold_active(std::mt19937 &rng) {
  if (!hold_command_triggered_) {
    hold_command_triggered_ = true;
    const auto to_hold = active_piece_.get_type();
    Tetromino next_piece{held_piece_.has_value() ? held_piece_.value()
                                                 : seven_bag_.pop(rng)};
    if (try_spawn_next(next_piece)) {
      held_piece_ = to_hold;
      lock_delay_.reset();
    } else {
      state_ = State::GameOver;
    }
  }
}

auto Tetris::try_spawn_next(Tetromino next) -> bool {
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

void Tetris::continue_to_next_turn(std::mt19937 &rng) {
  matrix_.lock_down(active_piece_);
  score_ += matrix_.clear_lines();

  {
    using namespace std::chrono_literals;
    static constexpr std::array LEVELS{1000ms, 900ms, 800ms, 700ms,
                                       600ms,  500ms, 450ms, 400ms,
                                       300ms,  200ms, 100ms};

    gravity_delay_.set_duration(score_ < 100 ? LEVELS[score_ / 10]
                                             : LEVELS.back());
  }

  if (try_spawn_next(Tetromino(seven_bag_.pop(rng)))) {
    hold_command_triggered_ = false;
    lock_delay_.reset();
  } else {
    state_ = State::GameOver;
  }
}
