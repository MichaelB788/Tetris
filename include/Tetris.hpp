#pragma once
#include "Matrix.hpp"
#include "PeriodicFunction.hpp"
#include "Piece.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <random>

class Tetris {
public:
  enum class State : uint8_t { Running, GameOver, Paused };

  struct HeldPiece {
    bool action_used{};
    std::optional<Piece::Type> type{};
  };

  struct SevenBag {
    using Preview = std::array<Piece::Type, 4>;
    size_t read_idx = 0;
    std::array<Piece::Type, 7> current{};
    std::array<Piece::Type, 7> next{
        Piece::Type::I, Piece::Type::O, Piece::Type::T, Piece::Type::S,
        Piece::Type::Z, Piece::Type::J, Piece::Type::L};
  };

  struct LockReset {
    uint8_t count{};
    bool countdown_enabled{};
    PeriodicFunction func;
  };

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

  void lock_piece();

  std::mt19937 &rng;

  State state{};
  unsigned score{};

  HeldPiece held_piece{};
  Matrix matrix{};
  Piece player{};
  SevenBag bag;

  PeriodicFunction gravity_func;
  LockReset lock_reset;
};

namespace tetris {
[[nodiscard]] auto create_next_piece(Piece::Type type) -> Piece;

namespace lock_reset {
void attempt_reset(Tetris::LockReset &lock_reset);
}

namespace seven_bag {
void shuffle(Tetris::SevenBag &bag, std::mt19937 &rng);
[[nodiscard]] auto pop(Tetris::SevenBag &bag, std::mt19937 &rng) -> Piece::Type;
[[nodiscard]] auto create_preview(const Tetris::SevenBag &bag)
    -> Tetris::SevenBag::Preview;
} // namespace seven_bag
} // namespace tetris
