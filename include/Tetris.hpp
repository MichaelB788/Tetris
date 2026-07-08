#pragma once
#include "Matrix.hpp"
#include "SevenBag.hpp"
#include "Tetromino.hpp"
#include "Timer.hpp"
#include <chrono>
#include <cstdint>
#include <random>

class Tetris {
public:
  Tetris(std::mt19937 &rng);

  enum class Action : uint8_t {
    MoveLeft,
    MoveRight,
    SoftDrop,
    HardDrop,
    RotateClockwise,
    RotateCounterclockwise,
    RotateHalf,
    Hold
  };
  void invoke_action(Action action, std::mt19937 &rng);

  void update(std::chrono::nanoseconds delta_time, std::mt19937 &rng);

  struct Snapshot {
    Tetromino active{};
    std::optional<Tetromino> held{};
    SevenBag::Preview seven_bag{};
    const Matrix &matrix{};
  };
  auto snapshot() const -> Snapshot {
    return {.active = active_,
            .held = held_,
            .seven_bag = seven_bag_.preview(),
            .matrix = matrix_};
  }

  auto score() const -> int { return score_; }

  auto game_over() const -> bool { return game_over_; }

private:
  // Sets the `game_over_` flag to true in the case of an unsuccessful
  // operation. Returns the success of the operation.
  auto attempt_swap(Tetromino next) -> bool;

  void complete_move(std::mt19937 &rng);

  void hold(std::mt19937 &rng);

  std::optional<Tetromino> held_{};
  Matrix matrix_{};
  SevenBag seven_bag_;
  Tetromino active_;

  int score_ = 0;
  bool hold_command_triggered_ = false;
  bool game_over_ = false;

  Timer lock_delay_{std::chrono::seconds{1}};
  Timer gravity_delay_{std::chrono::seconds{1}};
};
