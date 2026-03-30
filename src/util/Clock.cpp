#include "util/Clock.hpp"

void Clock::tick() {
  const TimePoint time_now = std::chrono::steady_clock::now();
  const auto delta_time = time_now - time_prev;
  ms_accumulator_ +=
      std::chrono::duration_cast<std::chrono::milliseconds>(delta_time);

  time_prev = time_now;
}
