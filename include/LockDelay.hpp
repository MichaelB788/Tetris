#pragma once
#include "Timer.hpp"
#include <chrono>
#include <random>

class Tetris;

class LockDelay {
public:
  LockDelay(std::chrono::nanoseconds delay) : timer_(delay) {};

  void begin_timer_if(bool cond);
  void perform_lock_reset_if(bool cond);
  void tick(std::chrono::nanoseconds delta, Tetris &tetris, std::mt19937 &rng);

  void reset();

private:
  bool lock_pending_ = false;
  unsigned lock_resets_ = 0;
  unsigned lock_reset_limit_ = 10;
  Timer<std::chrono::nanoseconds> timer_{std::chrono::seconds(1)};
};
