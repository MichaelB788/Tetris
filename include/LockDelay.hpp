#pragma once
#include "Timer.hpp"
#include <chrono>

class Tetris;

class LockDelay {
public:
  LockDelay(std::chrono::nanoseconds delay) : timer(delay) {};

  template <typename Fn>
  void tick(std::chrono::nanoseconds delta, Fn &&lock_func) {
    if (lock_pending) {
      timer.invoke_when_elapsed(delta, lock_func);
    }
  }

  void begin_timer_if(bool cond);
  void perform_lock_reset_if(bool cond);

  void reset();

private:
  bool lock_pending = false;
  unsigned lock_resets = 0;
  unsigned lock_reset_limit = 20;
  Timer timer{std::chrono::seconds(1)};
};
