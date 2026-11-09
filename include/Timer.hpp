#pragma once
#include <chrono>

class Timer {
public:
  Timer(std::chrono::nanoseconds dur = std::chrono::nanoseconds::zero())
      : duration(dur) {}

  void tick(std::chrono::nanoseconds delta);
  void rewind(std::chrono::nanoseconds amount);
  void reset();

  void set_duration(std::chrono::nanoseconds dur);

  [[nodiscard]] auto has_set_off() const -> bool;
  [[nodiscard]] auto get_duration() const -> std::chrono::nanoseconds;

private:
  std::chrono::nanoseconds duration{}, accumulator{};
};
