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
  static constexpr Point INIT_POS = {.x = 4, .y = 4};
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
  enum class State : uint8_t { Running, GameOver };

  explicit Tetris(std::mt19937 &rng)
      : seven_bag_(rng), active_piece_(seven_bag_.pop(rng), INIT_POS) {}

  void handle_command(Command command, std::mt19937 &rng);

  void tick(std::chrono::nanoseconds delta_time, std::mt19937 &rng);

  auto get_score() const -> int;
  auto get_state() const -> State;
  auto get_matrix() const -> const Matrix &;
  auto get_active_piece() const -> Tetromino;
  auto get_seven_bag() const -> SevenBag::Preview;
  auto get_held_piece() const -> std::optional<Tetromino::Type>;
  auto get_ghost_piece() const -> Tetromino;

private:
  void hold_active(std::mt19937 &rng);

  auto try_spawn_next(Tetromino next) -> bool;

  void continue_to_next_turn(std::mt19937 &rng);

  State state_ = State::Running;
  int score_ = 0;
  bool hold_command_triggered_ = false;

  Timer lock_delay_{std::chrono::seconds{1}};
  Timer gravity_delay_{std::chrono::seconds{1}};

  std::optional<Tetromino::Type> held_piece_{};
  Matrix matrix_{};
  SevenBag seven_bag_;
  Tetromino active_piece_;
};
