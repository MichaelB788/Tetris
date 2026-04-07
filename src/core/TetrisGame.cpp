#include "core/TetrisGame.hpp"
#include "core/Tetris_Move.hpp"

namespace {
constexpr Point INIT_POS = {.x = 4, .y = 2};
}

TetrisGame::TetrisGame() {
  hud_.next_queue.shuffle(rng_);
  board_.player = Tetromino(hud_.next_queue.pop(rng_), INIT_POS);
}

void TetrisGame::hard_drop() {
  board_.player.pos +=
      tetris::move::hard_drop_delta(board_.player, board_.matrix);
  complete_move();
}

void TetrisGame::hold() {
  if (hold_command_triggered)
    return;

  Tetromino::Type new_hold = board_.player.type;
  if (hud_.held_type.has_value()) {
    board_.player = Tetromino(hud_.held_type.value(), INIT_POS);
    hud_.held_type = new_hold;
  } else {
    hud_.held_type = new_hold;
    board_.player = Tetromino(hud_.next_queue.pop(rng_), INIT_POS);
  }

  hold_command_triggered = true;
}

auto TetrisGame::switch_to_next() -> bool {
  Tetromino next_piece = Tetromino(hud_.next_queue.pop(rng_), INIT_POS);

  for (int i = 0; i < 5; ++i) {
    if (board_.matrix.is_move_valid(next_piece.shape())) {
      board_.player = next_piece;
      return true;
    } else {
      next_piece.pos += Point::up();
    }
  }

  return false;
}

void TetrisGame::complete_move() {
  board_.matrix.place(board_.player);
  score_ += board_.matrix.clear_lines();

  if (switch_to_next()) {
    hold_command_triggered = false;
  } else {
    status_ = Status::GameOver;
  }
}
