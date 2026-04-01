#include "core/Tetris.hpp"

Tetris::Tetris() : rng_(std::random_device{}()) {
  next_queue_.shuffle(rng_);
  playfield_.switch_to_next(next_queue_);
}

void Tetris::drop() {
  playfield_.shift_player(playfield_.compute_drop_distance());
  complete_move();
}

void Tetris::hold() {
  if (hold_command_triggered)
    return;

  if (!playfield_.swap_with_held(held_)) {
    playfield_.switch_to_next(next_queue_);
    if (next_queue_.empty()) {
      next_queue_.shuffle(rng_);
    }
  }

  hold_command_triggered = true;
}

void Tetris::reset() {
  held_ = std::nullopt;
  hold_command_triggered = false;
  next_queue_.shuffle(rng_);
  playfield_.reset(next_queue_.pop());
  status_ = Status::Running;
  score_ = 0;
}

void Tetris::complete_move() {
  score_ += playfield_.lock_and_get_points();

  if (playfield_.switch_to_next(next_queue_)) {
    hold_command_triggered = false;
    if (next_queue_.empty()) {
      next_queue_.shuffle(rng_);
    }
  } else {
    status_ = Status::GameOver;
  }
}
