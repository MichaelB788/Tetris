#pragma once
#include "Matrix.hpp"
#include "PeriodicFunction.hpp"
#include "Point.hpp"
#include "SevenBag.hpp"
#include "Tetromino.hpp"
#include <cstdint>
#include <optional>
#include <random>

class Tetris {
public:
  static constexpr Point SPAWN_POINT = {.x = 4, .y = 4};
  enum class State : uint8_t { Running, GameOver, Paused };

  explicit Tetris(std::mt19937 &rng);

  void tick(std::chrono::nanoseconds delta_time);

  void move_left();
  void move_right();
  void soft_drop();
  void hard_drop();

  void rotate_cw();
  void rotate_ccw();
  void rotate_half();

  void hold_active();

  void pause();
  void unpause();

  void reset();

  [[nodiscard]] auto get_score() const -> unsigned;
  [[nodiscard]] auto get_state() const -> State;
  [[nodiscard]] auto get_matrix() const -> const Matrix &;
  [[nodiscard]] auto get_active_piece() const -> Tetromino;
  [[nodiscard]] auto get_seven_bag() const -> SevenBag::Preview;
  [[nodiscard]] auto get_held_piece() const -> std::optional<Tetromino::Type>;
  [[nodiscard]] auto get_ghost_piece() const -> Tetromino;

private:
  auto move_active(Point<int> delta) -> bool;
  auto rotate_active(Tetromino::Rotation next) -> bool;

  [[nodiscard]] auto try_spawn_next(Tetromino::Type next) -> bool;
  void update_level();

  void finalize_move();

  std::mt19937 &rng;

  State state = State::Running;

  unsigned score = 0;
  unsigned lock_resets = 0;
  bool hold_command_triggered = false;

  std::optional<Tetromino::Type> held_piece = std::nullopt;
  Matrix matrix{};
  SevenBag seven_bag;
  Tetromino active_piece;

  PeriodicFunction gravity;
  PeriodicFunction lock;
};
