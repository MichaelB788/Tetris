#include "core/TetrisGame.hpp"
#include "core/Tetris_Move.hpp"
#include <chrono>

namespace {
constexpr Point INIT_POS = {.x = 4, .y = 2};
}

TetrisGame::TetrisGame() {
  hud_.next_queue.shuffle(rng_);
  board_.player = Tetromino(hud_.next_queue.pop(rng_), INIT_POS);
}

void TetrisGame::tick() {
  gravity_delay_.tick();
  update_gravity();
  lock_delay_.tick();
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

void TetrisGame::update_level() {
  using namespace std::chrono_literals;
  static constexpr std::array<std::chrono::milliseconds, 11> LEVELS{
      1000ms, 900ms, 800ms, 700ms, 600ms, 500ms,
      450ms,  400ms, 350ms, 300ms, 200ms};

  if (score_ < 100) {
    gravity_delay_.activate_in(LEVELS[score_ / 10]);
  } else {
    gravity_delay_.activate_in(LEVELS.back());
  }
}

void TetrisGame::complete_move() {
  board_.matrix.place(board_.player);
  score_ += board_.matrix.clear_lines();
  update_level();

  if (switch_to_next()) {
    hold_command_triggered = false;
  } else {
    status_ = Status::GameOver;
  }
}

void TetrisGame::update_gravity() {
  if (gravity_delay_.has_set_off()) {
    soft_drop();
    gravity_delay_.reset();
  }
}
