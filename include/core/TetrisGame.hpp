#pragma once
#include "core/Matrix.hpp"
#include "core/NextQueue.hpp"
#include "core/Tetromino.hpp"
#include "util/Timer.hpp"
#include <chrono>
#include <cstdint>
#include <random>

class TetrisGame {
public:
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

  struct Snapshot {
    Tetromino active{};
    std::optional<Tetromino> held{};
    const NextQueue &next_queue{};
    const Matrix &matrix{};
  };

  TetrisGame(std::mt19937 &rng);

  void invoke_action(Action action, std::mt19937 &rng);

  void update(std::chrono::nanoseconds delta_time, std::mt19937 &rng);

  auto snapshot() const -> Snapshot {
    return {.active = active_,
            .held = held_,
            .next_queue = next_queue_,
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

  Tetromino active_{};
  std::optional<Tetromino> held_{};
  NextQueue next_queue_{};
  Matrix matrix_{};

  int score_ = 0;
  bool hold_command_triggered_ = false;
  bool game_over_ = false;

  Timer lock_delay_{std::chrono::seconds{1}};
  Timer gravity_delay_{std::chrono::seconds{1}};
};
