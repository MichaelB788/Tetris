#include "Tetris.hpp"
#include "Point.hpp"
#include "Tetromino.hpp"
#include <chrono>
#include <optional>

Tetris::Tetris(std::mt19937 &rng)
    : rng(rng), seven_bag(rng), active_piece(seven_bag.pop(), SPAWN_POINT),
      gravity(std::chrono::seconds(1), [this] { soft_drop(); }),
      lock(std::chrono::seconds(1), [this] {
        if (!matrix.is_move_valid(active_piece.get_shifted_shape({.y = 1}))) {
          lock_piece();
          state = start_next_round(seven_bag.pop());
        }
      }) {}

void Tetris::move_left() { move_active({.x = -1}); }

void Tetris::move_right() { move_active({.x = 1}); }

void Tetris::soft_drop() {
  should_lock = !active_piece.try_shift({.y = 1}, matrix);
}

void Tetris::hard_drop() {
  active_piece.hard_drop(matrix);
  lock_piece();
  state = start_next_round(seven_bag.pop());
}

void Tetris::rotate_cw() {
  rotate_active(tetromino::rotated_cw(active_piece.get_rotation(), 1));
}

void Tetris::rotate_ccw() {
  rotate_active(tetromino::rotated_cw(active_piece.get_rotation(), 3));
}

void Tetris::rotate_half() {
  rotate_active(tetromino::rotated_cw(active_piece.get_rotation(), 2));
}

void Tetris::hold_active() {
  if (hold_used)
    return;

  hold_used = true;

  // Perform a swap
  const auto temp = active_piece.get_type();
  state = start_next_round(held_piece.has_value() ? held_piece.value()
                                                  : seven_bag.pop());
  held_piece = temp;
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

  held_piece = std::nullopt;
  matrix.clear();
  seven_bag.shuffle();
  active_piece = {seven_bag.pop(), SPAWN_POINT};
}

auto Tetris::get_state() const -> State { return state; }

auto Tetris::get_score() const -> unsigned { return score; }

auto Tetris::get_matrix() const -> const Matrix & { return matrix; }

auto Tetris::get_active_piece() const -> Tetromino { return active_piece; }

auto Tetris::get_seven_bag() const -> SevenBag::Preview {
  return seven_bag.get_preview();
}

auto Tetris::get_held_piece() const -> std::optional<Tetromino::Type> {
  return held_piece;
}

auto Tetris::get_ghost_piece() const -> Tetromino {
  return {active_piece.get_type(), active_piece.get_pos_after_hard_drop(matrix),
          active_piece.get_rotation()};
}

void Tetris::move_active(FPoint delta) {
  if (active_piece.try_shift(delta, matrix) && should_lock) {
    if (lock_reset_count++ < 10)
      lock.reset();
  }
}

void Tetris::rotate_active(Tetromino::Rotation next) {
  if (active_piece.srs_rotation(next, matrix) && should_lock) {
    if (lock_reset_count++ < 10)
      lock.reset();
  }
}

auto Tetris::start_next_round(Tetromino::Type next) -> State {
  active_piece = {next, SPAWN_POINT};

  // Try to adjust the initial position of the next piece
  while (!matrix.is_move_valid(active_piece.get_shape())) {
    active_piece.shift({.y = -1});
    if (Matrix::is_out_of_bounds(active_piece.get_shape()))
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
  matrix.lock_down(active_piece);
  score += matrix.clear_lines();

  // Update the gravity duration based on the score
  using namespace std::chrono_literals;
  static constexpr std::array LEVELS{1000ms, 900ms, 800ms, 700ms, 600ms, 500ms,
                                     450ms,  400ms, 300ms, 200ms, 100ms};
  gravity.set_duration(score < 100 ? LEVELS[score / 10] : LEVELS.back());

  // Hold command should only be active again when the piece has locked down
  hold_used = false;
}
