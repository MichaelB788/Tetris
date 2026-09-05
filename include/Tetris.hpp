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

  void player_step_left();
  void player_step_right();

  void player_soft_drop();
  void player_hard_drop();

  void player_rotate_cw();
  void player_rotate_ccw();
  void player_rotate_half();

  void hold_current_piece();

  void pause_game();
  void unpause_game();

  void reset();

  [[nodiscard]] auto get_score() const -> unsigned;
  [[nodiscard]] auto get_state() const -> State;
  [[nodiscard]] auto get_matrix() const -> const Matrix &;
  [[nodiscard]] auto get_active_piece() const -> Piece;
  [[nodiscard]] auto get_seven_bag() const -> SevenBag::Preview;
  [[nodiscard]] auto get_held_piece() const -> std::optional<Piece::Type>;
  [[nodiscard]] auto get_ghost_piece() const -> Piece;

private:
  void player_horizontal_shift(float x);
  void player_rotate(Piece::Rotation next);

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

  State state = State::Running;

  bool hold_used = false;
  bool should_lock = false;

  std::optional<Piece::Type> held_type = std::nullopt;

  unsigned score = 0;
  unsigned lock_reset_count = 0;

  Matrix matrix{};
  SevenBag seven_bag;
  Piece player;

  PeriodicFunction gravity;
  PeriodicFunction lock;

  std::mt19937 &rng;
};
