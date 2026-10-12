#pragma once
#include "Matrix.hpp"
#include "PeriodicFunction.hpp"
#include "Piece.hpp"
#include "SevenBag.hpp"
#include <cstdint>
#include <optional>
#include <random>

class Tetris {
public:
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
  [[nodiscard]] auto get_seven_bag_preview() const -> SevenBag::Preview;
  [[nodiscard]] auto get_held_piece_type() const -> std::optional<Piece::Type>;
  [[nodiscard]] auto get_ghost_piece() const -> Piece;

private:
  void player_horizontal_shift(float x);
  void player_rotate(Piece::Rotation next);

  [[nodiscard]] auto start_next_round(Piece::Type next) -> State;

  void attempt_lock_reset();
  void lock_piece();

  std::mt19937 &rng;

  State state{};
  unsigned score{};

  struct {
    bool action_used{};
    std::optional<Piece::Type> type{};
  } held_piece{};
  Matrix matrix{};
  SevenBag seven_bag;
  Piece player;

  PeriodicFunction gravity_func;
  struct LockReset {
    PeriodicFunction func;
    uint8_t count{};
    bool countdown_enabled{};
  } lock_reset;
};
