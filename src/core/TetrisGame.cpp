#include "core/TetrisGame.hpp"
#include "core/Tetris_Move.hpp"
#include "core/Tetromino.hpp"
#include <chrono>
#include <cmath>
#include <random>

static constexpr Point INIT_POS = {.x = 4, .y = 4};

TetrisGame::TetrisGame(std::mt19937 &rng) {
  next_queue_.shuffle(rng);
  active_ = next_queue_.pop(rng);
  active_.pos = INIT_POS;
}

void TetrisGame::invoke_action(Action action, std::mt19937 &rng) {
  switch (action) {
    using enum Action;
  case MoveLeft:
    tetris::move::shift(active_, matrix_, {.x = -1});
    break;
  case MoveRight:
    tetris::move::shift(active_, matrix_, {.x = 1});
    break;
  case SoftDrop:
    tetris::move::shift(active_, matrix_, {.y = 1});
    break;
  case HardDrop:
    tetris::move::hard_drop(active_, matrix_);
    complete_move(rng);
    break;
  case RotateClockwise:
    tetris::srs::rotation(active_, matrix_, RotationDir::Clockwise);
    break;
  case RotateCounterclockwise:
    tetris::srs::rotation(active_, matrix_, RotationDir::CounterClockwise);
    break;
  case RotateHalf:
    tetris::srs::rotation(active_, matrix_, RotationDir::HalfTurn);
    break;
  case Hold:
    hold(rng);
    break;
  }
}

void TetrisGame::update(std::chrono::nanoseconds delta_time,
                        std::mt19937 &rng) {
  gravity_delay_.invoke_periodically(
      delta_time, [this] { tetris::move::shift(active_, matrix_, {.y = 1}); });

  if (!matrix_.is_move_valid(
          tetromino::shape_at(active_, active_.pos + Point{.y = 1}))) {
    lock_delay_.invoke_periodically(delta_time, [&] { complete_move(rng); });
  }
}

void TetrisGame::hold(std::mt19937 &rng) {
  if (!hold_command_triggered_) {
    hold_command_triggered_ = true;
    const auto to_hold = Tetromino(active_.type);
    attempt_swap(held_.has_value() ? held_.value() : next_queue_.pop(rng));
    held_ = to_hold;
  }
}

auto TetrisGame::attempt_swap(Tetromino next) -> bool {
  next.pos = INIT_POS;
  for (int i = 0; i < (Matrix::ROWS - INIT_POS.y); ++i) {
    if (matrix_.is_move_valid(tetromino::shape_of(next))) {
      active_ = next;
      return true;
    }
    --next.pos.y;
  }
  game_over_ = true;
  return false;
}

void TetrisGame::complete_move(std::mt19937 &rng) {
  // Place Tetromino and update scores
  matrix_.lock_down(active_);
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

  if (attempt_swap(next_queue_.pop(rng))) {
    hold_command_triggered_ = false;
    lock_delay_.reset();
  }
}
