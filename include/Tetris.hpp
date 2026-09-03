#pragma once
#include "Matrix.hpp"
#include "PeriodicFunction.hpp"
#include "Piece.hpp"
#include "Point.hpp"
#include "SevenBag.hpp"
#include <cstdint>
#include <optional>
#include <random>

class Tetris {
public:
  static constexpr FPoint SPAWN_POINT = {.x = 4, .y = 4};
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
  [[nodiscard]] auto get_active_piece() const -> Piece;
  [[nodiscard]] auto get_seven_bag() const -> SevenBag::Preview;
  [[nodiscard]] auto get_held_piece() const -> std::optional<Piece::Type>;
  [[nodiscard]] auto get_ghost_piece() const -> Piece;

private:
  void shift_active(FPoint delta);
  void rotate_active(Piece::Rotation next);

  /**
   * @brief Starts the next round by switching `active` to `next`. This will
   * also try to adjust the initial position of the new `active` piece if the
   * initial position overlaps with existing grounded tiles.
   *
   * @return `State::GameOver` if `active` was adjusted to a position out of
   * bounds, `State::Running` otherwise
   */
  [[nodiscard]] auto start_next_round(Piece::Type next) -> State;

  void lock_piece();

  std::mt19937 &rng;

  State state = State::Running;

  unsigned score = 0;
  unsigned lock_reset_count = 0;

  bool hold_used = false;
  bool should_lock = false;

  Matrix matrix{};
  SevenBag seven_bag;
  Piece player;
  std::optional<Piece::Type> held_type = std::nullopt;

  PeriodicFunction gravity;
  PeriodicFunction lock;
};
