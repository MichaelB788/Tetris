#include "Tetris.hpp"
#include "Piece.hpp"
#include "Point.hpp"
#include <chrono>
#include <optional>

Tetris::Tetris(std::mt19937 &rng)
    : rng(rng), seven_bag(rng), player(seven_bag.pop(), SPAWN_POINT),
      gravity(std::chrono::seconds(1), [this] { soft_drop(); }),
      lock(std::chrono::seconds(1), [this] {
        if (!matrix.can_place(
                piece::create_shape(piece::shift(player, {.y = 1})))) {
          lock_piece();
          state = start_next_round(seven_bag.pop());
        }
      }) {}

void Tetris::move_left() { shift_active({.x = -1}); }

void Tetris::move_right() { shift_active({.x = 1}); }

void Tetris::soft_drop() {
  should_lock = piece::shift_within(player, {.y = 1}, matrix) ==
                Piece::MoveResult::Unapplied;
}

void Tetris::hard_drop() {
  piece::hard_drop(player, matrix);
  lock_piece();
  state = start_next_round(seven_bag.pop());
}

void Tetris::rotate_cw() { rotate_active(Piece::Rotation::CW); }
void Tetris::rotate_ccw() { rotate_active(Piece::Rotation::CCW); }
void Tetris::rotate_half() { rotate_active(Piece::Rotation::Half); }

void Tetris::hold_active() {
  if (hold_used)
    return;

  hold_used = true;

  // Perform a swap
  const auto temp = player.type;
  state = start_next_round(held_type.has_value() ? held_type.value()
                                                 : seven_bag.pop());
  held_type = temp;
}

void Tetris::pause() {
  if (state == State::Running)
    state = State::Paused;
}

void Tetris::unpause() {
  if (state == State::Paused)
    state = State::Running;
}

void Tetris::tick(std::chrono::nanoseconds delta_time) {
  gravity.tick(delta_time);

  if (should_lock)
    lock.tick(delta_time);
}

void Tetris::reset() {
  state = State::Running;
  score = 0;
  hold_used = false;

  gravity.reset();
  lock.reset();

  held_type = std::nullopt;
  matrix.clear();
  seven_bag.shuffle();
  player = {seven_bag.pop(), SPAWN_POINT};
}

auto Tetris::get_state() const -> State { return state; }

auto Tetris::get_score() const -> unsigned { return score; }

auto Tetris::get_matrix() const -> const Matrix & { return matrix; }

auto Tetris::get_active_piece() const -> Piece { return player; }

auto Tetris::get_seven_bag() const -> SevenBag::Preview {
  return seven_bag.get_preview();
}

auto Tetris::get_held_piece() const -> std::optional<Piece::Type> {
  return held_type;
}

auto Tetris::get_ghost_piece() const -> Piece {
  auto ghost = player;
  piece::hard_drop(ghost, matrix);
  return ghost;
}

void Tetris::shift_active(FPoint delta) {
  switch (piece::shift_within(player, delta, matrix)) {
    using enum Piece::MoveResult;
  case Applied:
    if (should_lock && lock_reset_count < 10) {
      ++lock_reset_count;
      lock.reset();
    }
    break;
  case Unapplied:
    break;
  }
}

void Tetris::rotate_active(Piece::Rotation next) {
  switch (piece::rotate_srs(player, next, matrix)) {
    using enum Piece::MoveResult;
  case Applied:
    if (should_lock && lock_reset_count < 10) {
      ++lock_reset_count;
      lock.reset();
    }
    break;
  case Unapplied:
    break;
  }
}

auto Tetris::start_next_round(Piece::Type next) -> State {
  player = {next, SPAWN_POINT};

  // Try to adjust the initial position of the next piece
  while (!matrix.can_place(piece::create_shape(player))) {
    --player.pos.y;
    if (Matrix::is_out_of_bounds(piece::create_shape(player)))
      return State::GameOver;
  }

  // Adjustment successful, reset round specific variables for next round
  lock.reset();
  gravity.reset();
  lock_reset_count = 0;
  should_lock = false;

  return State::Running;
}

void Tetris::lock_piece() {
  // Lock down the active piece and update the score
  matrix.lock_down(player);
  score += matrix.clear_lines();

  // Update the gravity duration based on the score
  using namespace std::chrono_literals;
  static constexpr std::array LEVELS{1000ms, 900ms, 800ms, 700ms, 600ms, 500ms,
                                     450ms,  400ms, 300ms, 200ms, 100ms};
  gravity.set_duration(score < 100 ? LEVELS[score / 10] : LEVELS.back());

  // Hold command should only be active again when the piece has locked down
  hold_used = false;
}
