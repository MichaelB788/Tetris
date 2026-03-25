#include "Tetris.hpp"

Tetris::Tetris(mechanics::RotationSystem rs)
    : rs_(rs), hold_command_triggered_(false), state_(State::Running) {
  set_current(next_queue_.pop_next());
}

void Tetris::hold() {
  if (hold_command_triggered_)
    return;

  reset_current();
  if (hold_.has_value()) {
    const Tetromino temp = hold_.value();
    hold_ = current_;
    set_current(temp);
  } else {
    hold_ = current_;
    set_current(next_queue_.pop_next());
  }

  hold_command_triggered_ = true;
}

void Tetris::reset() {
  score_ = 0;
  state_ = State::Running;
  matrix_.clear();
  set_current(next_queue_.pop_next());
  hold_ = std::nullopt;
  hold_command_triggered_ = false;
}

void Tetris::reset_current() {
  current_.set_pos({.x = 0, .y = 0});
  while (current_.curr_rotation() != 0)
    current_.rotate_clockwise();
}

void Tetris::spawn_next() {
  mechanics::place(current_.projection(), matrix_);
  score_ += matrix_.clear_lines();
  high_score_ = std::max(score_, high_score_);

  if (mechanics::try_spawn(current_, next_queue_.pop_next(), matrix_)) {
    hold_command_triggered_ = false;
    update_ghost();
  } else {
    state_ = State::GameOver;
  }
}
