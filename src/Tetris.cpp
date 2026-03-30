#include "Tetris.hpp"

void Tetris::hold() {
  if (held_.command_triggered)
    return;

  Tetromino::Type new_hold = playfield_.player().type();
  if (held_.type.has_value()) {
    playfield_.set_player_unchecked(held_.type.value());
    held_.type = new_hold;
  } else {
    held_.type = new_hold;
    playfield_.set_player_unchecked(next_queue_.pop());
  }

  held_.command_triggered = true;
}

void Tetris::reset() {
  score_ = 0;
  next_queue_.shuffle();
  playfield_.reset(next_queue_.pop());
  status_ = Status::Running;
}

void Tetris::complete_move() {
  held_.command_triggered = false;
  score_ += playfield_.lock_and_get_points();
  if (!playfield_.set_player(next_queue_.pop())) {
    status_ = Status::GameOver;
  }
}
