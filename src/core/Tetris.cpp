#include "core/Tetris.hpp"

void Tetris::hold() {
  if (hold_command_triggered)
    return;

  Tetromino::Type new_hold = playfield_.player().type();
  if (held_.has_value()) {
    playfield_.set_player_unchecked(held_.value());
    held_ = new_hold;
  } else {
    held_ = new_hold;
    playfield_.set_player_unchecked(next_queue_.pop());
    if (next_queue_.empty()) {
      next_queue_.shuffle(rng_);
    }
  }

  hold_command_triggered = true;
}

void Tetris::reset() {
  score_ = 0;
  next_queue_.shuffle(rng_);
  playfield_.reset(next_queue_.pop());
  status_ = Status::Running;
}

void Tetris::complete_move() {
  hold_command_triggered = false;
  score_ += playfield_.lock_and_get_points();

  if (!playfield_.set_player(next_queue_.pop())) {
    status_ = Status::GameOver;
  }

  if (next_queue_.empty()) {
    next_queue_.shuffle(rng_);
  }
}
