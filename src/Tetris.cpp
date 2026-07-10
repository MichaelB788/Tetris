#include "Tetris.hpp"
#include "Tetromino.hpp"
#include <chrono>
#include <random>

static constexpr Point INIT_POS = {.x = 4, .y = 4};

Tetris::Tetris(std::mt19937 &rng)
    : seven_bag_(rng),
      active_piece_{.type = seven_bag_.pop(rng), .pos = INIT_POS} {}

void Tetris::invoke_action(Action action, std::mt19937 &rng) {
  switch (action) {
    using enum Action;
  case MoveLeft:
    tetromino::local_shift(active_piece_, {.x = -1}, matrix_);
    break;
  case MoveRight:
    tetromino::local_shift(active_piece_, {.x = 1}, matrix_);
    break;
  case SoftDrop:
    tetromino::local_shift(active_piece_, {.y = 1}, matrix_);
    break;
  case HardDrop:
    tetromino::hard_drop(active_piece_, matrix_);
    complete_move(rng);
    break;
  case RotateClockwise:
    tetromino::srs_rotation(active_piece_,
                            tetromino::cw_rotation(active_piece_), matrix_);
    break;
  case RotateCounterclockwise:
    tetromino::srs_rotation(active_piece_,
                            tetromino::ccw_rotation(active_piece_), matrix_);
    break;
  case RotateHalf:
    tetromino::srs_rotation(active_piece_,
                            tetromino::half_rotation(active_piece_), matrix_);
    break;
  case Hold:
    hold(rng);
    break;
  }
}

void Tetris::update(std::chrono::nanoseconds delta_time, std::mt19937 &rng) {
  gravity_delay_.invoke_periodically(
      [this] { tetromino::local_shift(active_piece_, {.y = 1}, matrix_); },
      delta_time);

  if (!matrix_.is_move_valid(tetromino::shape_at(
          active_piece_, active_piece_.pos + Point{.y = 1}))) {
    lock_delay_.invoke_periodically([&] { complete_move(rng); }, delta_time);
  }
}

auto Tetris::ghost_piece() const -> Tetromino {
  Tetromino ghost = active_piece_;
  tetromino::hard_drop(ghost, matrix_);
  return ghost;
}

void Tetris::hold(std::mt19937 &rng) {
  if (!hold_command_triggered_) {
    hold_command_triggered_ = true;
    const auto to_hold = active_piece_.type;
    attempt_swap(Tetromino{.type = held_piece_.has_value()
                                       ? held_piece_.value()
                                       : seven_bag_.pop(rng)});
    held_piece_ = to_hold;
    lock_delay_.reset();
  }
}

auto Tetris::attempt_swap(Tetromino next) -> bool {
  active_piece_ = next;
  auto new_pos = INIT_POS;
  for (int i = 0; i < (MATRIX_ROWS - INIT_POS.y); ++i) {
    if (matrix_.is_move_valid(tetromino::shape_at(active_piece_, new_pos))) {
      active_piece_.pos = new_pos;
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

  if (attempt_swap(Tetromino{.type = seven_bag_.pop(rng)})) {
    hold_command_triggered_ = false;
    lock_delay_.reset();
  } else {
    game_over_ = true;
  }
}
