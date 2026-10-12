#include "Tetris.hpp"
#include "FPoint.hpp"
#include "Piece.hpp"
#include "rules.hpp"
#include <chrono>
#include <optional>
#include <random>

namespace {
[[nodiscard]] auto create_next_piece(Piece::Type type) -> Piece {
  return {.type = type, .pos = {4, 4}};
}

void attempt_lock_reset(Tetris::LockReset &lock_reset) {
  if (lock_reset.countdown_enabled && lock_reset.count < 10) {
    ++lock_reset.count;
    lock_reset.func.reset();
  }
}
} // namespace

Tetris::Tetris(std::mt19937 &rng_)
    : rng(rng_), seven_bag(rng_),
      player(create_next_piece(seven_bag.pop_next_type())),
      gravity_func(std::chrono::seconds(1), [this] { player_soft_drop(); }),
      lock_reset{.func{std::chrono::seconds(1), [this] {
                         if (!piece_action::shift(player, {.y = 1}, matrix)) {
                           lock_piece();
                           state = start_next_round(seven_bag.pop_next_type());
                         }
                       }}} {}

void Tetris::player_step_left() { player_horizontal_shift(-1); }

void Tetris::player_step_right() { player_horizontal_shift(1); }

void Tetris::player_soft_drop() {
  if (const auto shifted = piece_action::shift(player, {.y = 1}, matrix))
    player = shifted.value();
  else
    lock_reset.countdown_enabled = true;
}

void Tetris::player_hard_drop() {
  player = piece_action::hard_drop(player, matrix);
  lock_piece();
  state = start_next_round(seven_bag.pop_next_type());
}

void Tetris::player_rotate_cw() { player_rotate(Piece::Rotation::r90); }

void Tetris::player_rotate_ccw() { player_rotate(Piece::Rotation::r270); }

void Tetris::player_rotate_half() { player_rotate(Piece::Rotation::r180); }

void Tetris::hold_current_piece() {
  if (!held_piece.action_used) {
    const auto temp = player.type;
    state = start_next_round(held_piece.type ? held_piece.type.value()
                                             : seven_bag.pop_next_type());
    held_piece.type = temp;
    held_piece.action_used = true;
  }
}

void Tetris::pause_game() {
  if (state == State::Running)
    state = State::Paused;
}

void Tetris::unpause_game() {
  if (state == State::Paused)
    state = State::Running;
}

void Tetris::tick(std::chrono::nanoseconds delta_time) {
  gravity_func.tick(delta_time);

  if (lock_reset.countdown_enabled)
    lock_reset.func.tick(delta_time);
}

void Tetris::reset() {
  state = State::Running;
  score = lock_reset.count = 0;
  held_piece.action_used = lock_reset.countdown_enabled = false;

  gravity_func.reset();
  lock_reset.func.reset();

  held_piece.type = std::nullopt;
  matrix.clear_all();
  seven_bag.shuffle();
  player = create_next_piece(seven_bag.pop_next_type());
}

void Tetris::player_horizontal_shift(float x) {
  if (const auto shifted = piece_action::shift(player, {.x = x}, matrix)) {
    player = shifted.value();
    attempt_lock_reset(lock_reset);
  }
}

void Tetris::player_rotate(Piece::Rotation next) {
  if (const auto rotated = piece_action::srs_rotation(player, next, matrix)) {
    player = rotated.value();
    attempt_lock_reset(lock_reset);
  }
}

auto Tetris::start_next_round(Piece::Type next) -> State {
  player = create_next_piece(next);

  // Try to adjust the initial position of the next piece
  while (!piece_query::is_valid_shape(player.get_shape(), matrix)) {
    --player.pos.y;
    if (!piece_query::is_shape_within_bounds(player.get_shape()))
      return State::GameOver;
  }

  // Adjustment successful, reset round specific variables for next round
  lock_reset.func.reset();
  gravity_func.reset();
  lock_reset.count = 0;
  lock_reset.countdown_enabled = false;

  return State::Running;
}

void Tetris::lock_piece() {
  held_piece.action_used = false;
  piece_action::lock_down(player, matrix);
  score += matrix.clear_lines();

  using namespace std::chrono_literals;
  static constexpr std::array LEVELS{1000ms, 900ms, 800ms, 700ms, 600ms, 500ms,
                                     450ms,  400ms, 300ms, 200ms, 100ms};
  gravity_func.set_duration(score < 100 ? LEVELS[score / 10]
                                        : std::chrono::milliseconds(100));
}

auto Tetris::get_state() const -> State { return state; }

auto Tetris::get_score() const -> unsigned { return score; }

auto Tetris::get_matrix() const -> const Matrix & { return matrix; }

auto Tetris::get_active_piece() const -> Piece { return player; }

auto Tetris::get_seven_bag_preview() const -> SevenBag::Preview {
  return seven_bag.get_preview();
}

auto Tetris::get_held_piece_type() const -> std::optional<Piece::Type> {
  return held_piece.type;
}

auto Tetris::get_ghost_piece() const -> Piece {
  return piece_action::hard_drop(player, matrix);
}
