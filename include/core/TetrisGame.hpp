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
    tetris::move::shift(board_.player, board_.matrix, Point::left());
  }

  void move_right() {
    tetris::move::shift(board_.player, board_.matrix, Point::right());
  }

  void soft_drop() {
    tetris::move::shift(board_.player, board_.matrix, Point::down());
  }

  void hard_drop();

  void rotate_cw() {
    tetris::srs::rotation(board_.player, board_.matrix, RotationDir::CW);
  }

  void rotate_ccw() {
    tetris::srs::rotation(board_.player, board_.matrix, RotationDir::CCW);
  }

  void hold();

  [[nodiscard]] auto board() const -> const Board & { return board_; }

  [[nodiscard]] auto hud() const -> const HUD & { return hud_; }

  [[nodiscard]] auto status() const -> Status { return status_; }

  [[nodiscard]] auto score() const -> int { return score_; }

private:
  [[nodiscard]] auto switch_to_next() -> bool;

  void update_level();

  void complete_move();

  HUD hud_{};

  Board board_{};

  std::mt19937 rng_{std::random_device{}()};

  bool hold_command_triggered_ = false;

  Status status_ = Status::Running;

  int score_ = 0;

  Timer lock_delay_{.duration = std::chrono::seconds{1}};

  Timer gravity_delay_{.duration = std::chrono::seconds{1}};
};
