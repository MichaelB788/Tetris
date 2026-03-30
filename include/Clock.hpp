#pragma once
#include <chrono>

class Clock {
public:
  using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

  explicit Clock(const std::chrono::milliseconds &ms_until_activation)
      : time_prev(std::chrono::steady_clock::now()),
        ms_accumulator_(std::chrono::milliseconds::zero()),
        ms_to_activate_(ms_until_activation) {}

  void tick();

  [[nodiscard]] bool has_set_off() const {
    return ms_accumulator_ >= ms_to_activate_;
  }

  void reset() { ms_accumulator_ = std::chrono::milliseconds::zero(); }

  void activate_in(const std::chrono::milliseconds ms) { ms_to_activate_ = ms; }

private:
  TimePoint time_prev;

  std::chrono::milliseconds ms_accumulator_;

  std::chrono::milliseconds ms_to_activate_;
};
