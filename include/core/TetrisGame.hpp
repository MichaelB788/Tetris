#pragma once
#include "core/TetrisGame_Types.hpp"
#include "core/Tetris_Move.hpp"
#include "util/Timer.hpp"
#include <chrono>
#include <random>

class TetrisGame {
public:
  TetrisGame();

  void update(std::chrono::nanoseconds delta_time);

  void move_left() {
    tetris::move::shift(board_.player, board_.matrix, {.x = -1});
  }

  void move_right() {
    tetris::move::shift(board_.player, board_.matrix, {.x = 1});
  }

  void soft_drop() {
    tetris::move::shift(board_.player, board_.matrix, {.y = 1});
  }

  void hard_drop() {
    tetris::move::hard_drop(board_.player, board_.matrix);
    complete_move();
  }

  void rotate_cw() {
    tetris::srs::rotation(board_.player, board_.matrix, RotationDir::Clockwise);
  }

  void rotate_ccw() {
    tetris::srs::rotation(board_.player, board_.matrix,
                          RotationDir::CounterClockwise);
  }

  void rotate_ht() {
    tetris::srs::rotation(board_.player, board_.matrix, RotationDir::HalfTurn);
  }

  void hold();

  [[nodiscard]] auto board() const -> const Board & { return board_; }

  [[nodiscard]] auto hud() const -> const HUD & { return hud_; }

  [[nodiscard]] auto status() const -> Status { return status_; }

  [[nodiscard]] auto score() const -> int { return score_; }

private:
  [[nodiscard]] auto switch_to_next(Tetromino::Type next) -> bool;

  void update_level();

  void complete_move();

  bool hold_command_triggered_ = false;

  Status status_ = Status::Running;

  int score_ = 0;

  Timer lock_delay_{std::chrono::seconds{1}};

  Timer gravity_delay_{std::chrono::seconds{1}};

  HUD hud_{};

  Board board_{};

  std::mt19937 rng_{std::random_device{}()};
};
