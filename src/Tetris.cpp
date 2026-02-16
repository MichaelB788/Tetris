#include "Tetris.hpp"

Tetris::Tetris(mechanics::RotationSystem rs)
    : rs_(rs), hold_command_triggered_(false), state_(State::Running) {
  current_ = next_queue_.pop_next();
  update_ghost();
}

void Tetris::hold() {
  if (hold_command_triggered_)
    return;

  reset_current();
  if (hold_.has_value()) {
    const Tetromino temp = hold_.value();
    hold_ = current_;
    current_ = temp;
  } else {
    hold_ = current_;
    current_ = next_queue_.pop_next();
  }

  update_ghost();
  hold_command_triggered_ = true;
}

void Tetris::reset() {
  state_ = State::Running;
  matrix_.clear();
  current_ = next_queue_.pop_next();
  hold_ = std::nullopt;
  hold_command_triggered_ = false;
}

void Tetris::reset_current() {
  current_.set_position(Tetromino::INITIAL_POSITION);
  while (current_.curr_rotation() != 0)
    current_.rotate_clockwise();
}

void Tetris::spawn_next() {
  mechanics::place(current_.projection(), matrix_);
  points_ = matrix_.clear_lines();

  if (mechanics::try_spawn(current_, next_queue_.pop_next(), matrix_)) {
    hold_command_triggered_ = false;
    update_ghost();
  } else {
    state_ = State::GameOver;
  }
}
