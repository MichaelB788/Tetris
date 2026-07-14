#pragma once
#include "Matrix.hpp"
#include "Point.hpp"
#include "SevenBag.hpp"
#include "Tetromino.hpp"
#include "Timer.hpp"
#include <chrono>
#include <cstdint>
#include <optional>
#include <random>

class Tetris {
public:
  static constexpr Point INIT_POS = {.x = 4, .y = 4};
  enum class State : uint8_t { Running, GameOver, Paused };

  explicit Tetris(std::mt19937 &rng)
      : seven_bag_(rng), active_piece_(seven_bag_.pop(rng), INIT_POS) {}

  void tick(std::chrono::nanoseconds delta_time, std::mt19937 &rng);

  void move_left();
  void move_right();
  void soft_drop();
  void hard_drop(std::mt19937 &rng);

  void rotate_cw();
  void rotate_ccw();
  void rotate_half();

  void hold_active(std::mt19937 &rng);

  void toggle_pause();

  void reset(std::mt19937 &rng);

  auto get_score() const -> unsigned;
  auto get_state() const -> State;
  auto get_matrix() const -> const Matrix &;
  auto get_active_piece() const -> Tetromino;
  auto get_seven_bag() const -> SevenBag::Preview;
  auto get_held_piece() const -> std::optional<Tetromino::Type>;
  auto get_ghost_piece() const -> Tetromino;

private:
  void shift_active(Point<int> delta);
  void rotate_active(Tetromino::Rotation next);

  auto try_spawn_next(Tetromino::Type next) -> bool;
  void update_level();
  void continue_to_next_turn(std::mt19937 &rng);

  State state_ = State::Running;
  unsigned score_ = 0;
  unsigned lock_resets_ = 0;
  unsigned lock_reset_limit_ = 10;
  bool lock_pending_ = false;
  bool hold_command_triggered_ = false;

  Timer<std::chrono::nanoseconds> gravity_delay_{std::chrono::seconds(1)};
  Timer<std::chrono::nanoseconds> lock_delay_{gravity_delay_.duration() * 2};

  std::optional<Tetromino::Type> held_piece_ = std::nullopt;
  Matrix matrix_{};
  SevenBag seven_bag_;
  Tetromino active_piece_;
};
