#include "core/TetrisGame.hpp"
#include "core/Tetris_Move.hpp"
#include <chrono>

namespace {
constexpr Point INIT_POS = {.x = 4, .y = 4};
}

TetrisGame::TetrisGame() {
  hud_.next_queue.shuffle(rng_);
  board_.player = Tetromino(hud_.next_queue.pop(rng_), INIT_POS);
}

void TetrisGame::update(std::chrono::nanoseconds delta_time) {
  // Update gravity
  gravity_delay_.invoke_periodically(delta_time, [this] { soft_drop(); });

  // Update lock delay elapsed time only if a soft drop has failed (in other
  // words, the piece is touching the ground).
  if (!board_.matrix.is_move_valid(board_.player.shifted(Point::down())))
    lock_delay_.invoke_periodically(delta_time, [this] { complete_move(); });
}

void TetrisGame::hold() {
  if (hold_command_triggered_)
    return;

  Tetromino::Type new_hold = board_.player.type;
  if (hud_.held_type.has_value()) {
    if (!switch_to_next(hud_.held_type.value())) {
      status_ = Status::GameOver;
      return;
    }
    hud_.held_type = new_hold;
  } else {
    hud_.held_type = new_hold;
    if (!switch_to_next(hud_.held_type.value())) {
      status_ = Status::GameOver;
      return;
    }
  }

  hold_command_triggered_ = true;
}

auto TetrisGame::switch_to_next(Tetromino::Type next) -> bool {
  Tetromino next_piece = Tetromino(next, INIT_POS);

  for (int i = 0; i < (Matrix::ROWS - INIT_POS.y); ++i) {
    if (board_.matrix.is_move_valid(next_piece.shape())) {
      board_.player = next_piece;
      return true;
    } else {
      next_piece.pos += Point::up();
    }
  }

  return false;
}

void TetrisGame::update_level() {
  using namespace std::chrono_literals;
  static constexpr std::array<std::chrono::milliseconds, 11> LEVELS{
      1000ms, 900ms, 800ms, 700ms, 600ms, 500ms,
      450ms,  400ms, 300ms, 200ms, 100ms};

  gravity_delay_.set_duration(score_ < 100 ? LEVELS[score_ / 10]
                                           : LEVELS.back());
}

void TetrisGame::complete_move() {
  board_.matrix.place(board_.player);
  score_ += board_.matrix.clear_lines();
  update_level();

  if (switch_to_next(hud_.next_queue.pop(rng_))) {
    hold_command_triggered_ = false;
    lock_delay_.reset();
  } else {
    status_ = Status::GameOver;
  }
}
