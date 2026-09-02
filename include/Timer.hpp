#pragma once
#include <chrono>

class Timer {
public:
  Timer(const Timer &) = delete;
  Timer(Timer &&) = delete;
  Timer &operator=(const Timer &) = delete;
  Timer &operator=(Timer &&) = delete;

  Timer(std::chrono::nanoseconds dur) : duration(dur) {}

  void tick(std::chrono::nanoseconds delta);

  void rewind(std::chrono::nanoseconds amount);

  void reset();

  void set_duration(std::chrono::nanoseconds dur);

  [[nodiscard]] auto has_set_off() const -> bool;

  [[nodiscard]] auto get_duration() const -> std::chrono::nanoseconds;

private:
  std::chrono::nanoseconds duration{};
  std::chrono::nanoseconds accumulator{};
};
