#pragma once
#include <chrono>

class Timer {
public:
  constexpr Timer() = default;

  constexpr Timer(std::chrono::nanoseconds dur) : duration(dur) {}

  void operator+=(std::chrono::nanoseconds delta) { accumulator += delta; }

  template <typename Fn>
  void invoke_when_elapsed(std::chrono::nanoseconds delta, Fn &&function) {
    accumulator += delta;
    if (has_elapsed()) {
      function();
    }
  }

  template <typename Fn>
  void invoke_periodically(std::chrono::nanoseconds delta, Fn &&function) {
    accumulator += delta;
    while (has_elapsed()) {
      accumulator -= duration;
      function();
    }
  }

  void set_duration(std::chrono::nanoseconds dur) { duration = dur; }

  void reset() { accumulator = {}; }

  [[nodiscard]] auto has_elapsed() const -> bool {
    return accumulator >= duration;
  }

  [[nodiscard]] auto get_duration() const -> std::chrono::nanoseconds {
    return duration;
  }

  [[nodiscard]] auto get_accumulator() const -> std::chrono::nanoseconds {
    return accumulator;
  }

private:
  std::chrono::nanoseconds duration{}, accumulator{};
};
