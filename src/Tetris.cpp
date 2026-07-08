#include "Tetris.hpp"
#include "Tetromino.hpp"
#include <chrono>
#include <cmath>
#include <random>

static constexpr Point INIT_POS = {.x = 4, .y = 4};

Tetris::Tetris(std::mt19937 &rng)
    : seven_bag_(rng), active_piece_(seven_bag_.pop(rng)) {
  active_piece_.pos = INIT_POS;
}

void Tetris::invoke_action(Action action, std::mt19937 &rng) {
  switch (action) {
    using enum Action;
  case MoveLeft:
    local_shift(active_piece_, {.x = -1}, matrix_);
    break;
  case MoveRight:
    local_shift(active_piece_, {.x = 1}, matrix_);
    break;
  case SoftDrop:
    local_shift(active_piece_, {.y = 1}, matrix_);
    break;
  case HardDrop:
    hard_drop(active_piece_, matrix_);
    complete_move(rng);
    break;
  case RotateClockwise:
    srs_rotation(active_piece_, RotationDir::Clockwise, matrix_);
    break;
  case RotateCounterclockwise:
    srs_rotation(active_piece_, RotationDir::CounterClockwise, matrix_);
    break;
  case RotateHalf:
    srs_rotation(active_piece_, RotationDir::HalfTurn, matrix_);
    break;
  case Hold:
    hold(rng);
    break;
  }
}

void Tetris::update(std::chrono::nanoseconds delta_time, std::mt19937 &rng) {
  gravity_delay_.invoke_periodically(
      [this] { local_shift(active_piece_, {.y = 1}, matrix_); }, delta_time);

  if (!matrix_.is_move_valid(
          shape_at(active_piece_, active_piece_.pos + Point{.y = 1}))) {
    lock_delay_.invoke_periodically([&] { complete_move(rng); }, delta_time);
  }
}

auto Tetris::ghost_piece() const -> Tetromino {
  Tetromino ghost = active_piece_;
  hard_drop(ghost, matrix_);
  return ghost;
}

void Tetris::hold(std::mt19937 &rng) {
  if (!hold_command_triggered_) {
    hold_command_triggered_ = true;
    const auto to_hold = Tetromino(active_piece_.type);
    attempt_swap(held_piece_.has_value() ? held_piece_.value()
                                         : seven_bag_.pop(rng));
    held_piece_ = to_hold;
    lock_delay_.reset();
  }
}

auto Tetris::attempt_swap(Tetromino next) -> bool {
  next.pos = INIT_POS;
  for (int i = 0; i < (MATRIX_ROWS - INIT_POS.y); ++i) {
    if (matrix_.is_move_valid(shape_of(next))) {
      active_piece_ = next;
      return true;
    }
    --next.pos.y;
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
    static constexpr std::array<std::chrono::milliseconds, 11> LEVELS{
        1000ms, 900ms, 800ms, 700ms, 600ms, 500ms,
        450ms,  400ms, 300ms, 200ms, 100ms};

    gravity_delay_.set_duration(score_ < 100 ? LEVELS[score_ / 10]
                                             : LEVELS.back());
  }

  if (attempt_swap(seven_bag_.pop(rng))) {
    hold_command_triggered_ = false;
    lock_delay_.reset();
  } else {
    game_over_ = true;
  }
}
