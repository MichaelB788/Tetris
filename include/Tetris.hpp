#pragma once
#include "Piece.hpp"
#include "Playfield.hpp"
#include "SevenBag.hpp"
#include "Timer.hpp"
#include <chrono>
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

  void player_rotate_clockwise();
  void player_rotate_counterclockwise();

  void hold_current_piece();

  void pause_game();
  void unpause_game();

  void reset();

  [[nodiscard]] auto get_score() const -> unsigned;
  [[nodiscard]] auto get_state() const -> State;
  [[nodiscard]] auto get_playfield() const -> const Playfield &;
  [[nodiscard]] auto get_active_piece() const -> Piece;
  [[nodiscard]] auto get_seven_bag_preview() const -> SevenBag::Preview;
  [[nodiscard]] auto get_held_piece_type() const -> std::optional<Piece::Type>;
  [[nodiscard]] auto get_ghost_piece() const -> Piece;

private:
  struct HeldPiece {
    bool action_used{};
    std::optional<Piece::Type> type{};
  };

  struct Lock {
    bool is_enabled{};
    uint8_t reset_count{};
    Timer delay{std::chrono::seconds{1}};

    void attempt_reset();
  };

  void player_horizontal_shift(float x);
  void player_rotate(Piece::RotationDir dir);

  [[nodiscard]] auto start_next_round(Piece::Type next_type) -> State;

  std::mt19937 &rng;

  State state{};
  unsigned score{};

  Timer gravity_delay{std::chrono::seconds{1}};
  Lock lock{};

  HeldPiece held_piece{};
  Playfield playfield{};
  SevenBag seven_bag;
  Piece player;
};
