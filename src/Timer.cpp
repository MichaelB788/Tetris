#include "Timer.hpp"

void Timer::tick(std::chrono::nanoseconds delta) { accumulator += delta; }

void Timer::rewind(std::chrono::nanoseconds amount) { accumulator -= amount; }

void Timer::reset() { accumulator = std::chrono::nanoseconds::zero(); }

void Timer::set_duration(std::chrono::nanoseconds dur) { duration = dur; }

auto Timer::has_set_off() const -> bool { return accumulator >= duration; }

auto Timer::get_duration() const -> std::chrono::nanoseconds {
  return duration;
}
