#include "Tetris.hpp"
#include "Geometry.hpp"
#include "Piece.hpp"
#include <chrono>
#include <optional>
#include <random>

static constexpr Point SPAWN_POS = {4, 4};

Tetris::Tetris(std::mt19937 &rng_)
    : rng(rng_), seven_bag(rng_), player(seven_bag.pop_next_type(), SPAWN_POS),
      gravity_func(std::chrono::seconds(1), [this] { player_soft_drop(); }),
      lock_reset{{std::chrono::seconds(1), [this] {
                    auto test = player;
                    if (!test.shift({0, 1}, playfield)) {
                      lock_piece();
                      state = start_next_round(seven_bag.pop_next_type());
                    }
                  }}} {}

void Tetris::player_step_left() { player_horizontal_shift(-1); }

void Tetris::player_step_right() { player_horizontal_shift(1); }

void Tetris::player_soft_drop() {
  if (!player.shift({0, 1}, playfield))
    lock_reset.countdown_enabled = true;
}

void Tetris::player_hard_drop() {
  player.hard_drop(playfield);
  lock_piece();
  state = start_next_round(seven_bag.pop_next_type());
}

void Tetris::player_rotate_clockwise() {
  player_rotate(Piece::RotationDir::Clockwise);
}

void Tetris::player_rotate_counterclockwise() {
  player_rotate(Piece::RotationDir::Counterclockwise);
}

void Tetris::hold_current_piece() {
  if (!held_piece.action_used) {
    const auto temp = player.get_type();
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
  playfield.clear_all_rows();
  seven_bag.shuffle();
  player = {seven_bag.pop_next_type(), SPAWN_POS};
}

void Tetris::player_horizontal_shift(float x) {
  if (player.shift({x, 0}, playfield))
    attempt_lock_reset();
}

void Tetris::player_rotate(Piece::RotationDir dir) {
  if (player.rotate(dir, playfield))
    attempt_lock_reset();
}

auto Tetris::start_next_round(Piece::Type next_type) -> State {
  player = {next_type, SPAWN_POS};

  // Try to adjust the initial position of the next piece
  while (!playfield.can_place(player.get_shape())) {
    player.shift_unchecked({0, -1});
    if (!playfield.is_within_bounds(player.get_shape()))
      return State::GameOver;
  }

  // Adjustment successful, reset round specific variables for next round
  lock_reset.func.reset();
  gravity_func.reset();
  lock_reset.count = 0;
  lock_reset.countdown_enabled = false;

  return State::Running;
}

void Tetris::attempt_lock_reset() {
  if (lock_reset.countdown_enabled && lock_reset.count < 10) {
    ++lock_reset.count;
    lock_reset.func.reset();
  }
}

void Tetris::lock_piece() {
  held_piece.action_used = false;
  playfield.lock_down(player);
  score += playfield.clear_full_rows();

  using namespace std::chrono_literals;
  static constexpr std::array LEVELS{1000ms, 900ms, 800ms, 700ms, 600ms, 500ms,
                                     450ms,  400ms, 300ms, 200ms, 100ms};
  gravity_func.set_duration(score < 100 ? LEVELS[score / 10]
                                        : std::chrono::milliseconds(100));
}

auto Tetris::get_state() const -> State { return state; }

auto Tetris::get_score() const -> unsigned { return score; }

auto Tetris::get_playfield() const -> const Playfield & { return playfield; }

auto Tetris::get_active_piece() const -> Piece { return player; }

auto Tetris::get_seven_bag_preview() const -> SevenBag::Preview {
  return seven_bag.get_preview();
}

auto Tetris::get_held_piece_type() const -> std::optional<Piece::Type> {
  return held_piece.type;
}

auto Tetris::get_ghost_piece() const -> Piece {
  auto ghost = player;
  ghost.hard_drop(playfield);
  return ghost;
}
