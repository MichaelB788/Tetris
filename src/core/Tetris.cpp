#include "core/Tetris.hpp"
#include "core/tetris-move.hpp"

Tetris::Tetris() {
  hud_.next_queue.shuffle(rng_);
  board_.player = Tetromino(hud_.next_queue.pop(rng_), INIT_POS);
}

void Tetris::drop() {
  board_.player = tetris::move::compute_dropped(board_.player, board_.matrix);
  complete_move();
}

void Tetris::hold() {
  if (hold_command_triggered)
    return;

  Tetromino::Type new_hold = board_.player.type();
  if (hud_.held_type.has_value()) {
    board_.player = Tetromino(hud_.held_type.value(), INIT_POS);
    hud_.held_type = new_hold;
  } else {
    hud_.held_type = new_hold;
    board_.player = Tetromino(hud_.next_queue.pop(rng_), INIT_POS);
  }

  hold_command_triggered = true;
}

bool Tetris::switch_to_next() {
  Tetromino next_piece = Tetromino(hud_.next_queue.pop(rng_), INIT_POS);

  for (int i = 0; i < 5; ++i) {
    if (board_.matrix.is_move_valid(next_piece.shape())) {
      board_.player = next_piece;
      return true;
    } else {
      next_piece.shift(Point::up());
    }
  }

  return false;
}

void Tetris::complete_move() {
  board_.matrix.place(board_.player);
  score_ += board_.matrix.clear_lines();

  if (switch_to_next()) {
    hold_command_triggered = false;
  } else {
    status_ = Status::GameOver;
  }
}
