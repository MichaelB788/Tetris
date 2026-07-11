#pragma once
#include "Matrix.hpp"
#include "SevenBag.hpp"
#include "Tetromino.hpp"
#include "Timer.hpp"
#include <chrono>
#include <random>

class Tetris {
public:
  enum class Command : uint8_t {
    MoveLeft,
    MoveRight,
    SoftDrop,
    HardDrop,
    RotateClockwise,
    RotateCounterclockwise,
    RotateHalf,
    Hold
  };

  explicit Tetris(std::mt19937 &rng);

  void invoke_action(Command action, std::mt19937 &rng);

  void tick(std::chrono::nanoseconds delta_time, std::mt19937 &rng);

  auto score() const -> int { return score_; }
  auto game_over() const -> bool { return game_over_; }
  auto matrix() const -> const Matrix & { return matrix_; }
  auto active_piece() const -> Tetromino { return active_piece_; }
  auto seven_bag() const -> SevenBag::Preview { return seven_bag_.preview(); }
  auto held_piece() const -> std::optional<Tetromino::Type> {
    return held_piece_;
  }

  auto ghost_piece() const -> Tetromino;

private:
  // Sets the `game_over_` flag to true in the case of an unsuccessful
  // operation. Returns the success of the operation.
  auto attempt_swap(Tetromino next) -> bool;

  void complete_move(std::mt19937 &rng);

  void hold(std::mt19937 &rng);

  int score_ = 0;
  bool hold_command_triggered_ = false;
  bool game_over_ = false;

  Timer lock_delay_{std::chrono::seconds{1}};
  Timer gravity_delay_{std::chrono::seconds{1}};

  std::optional<Tetromino::Type> held_piece_{};
  Matrix matrix_{};
  SevenBag seven_bag_;
  Tetromino active_piece_;
};
