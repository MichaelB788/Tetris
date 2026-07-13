#pragma once

template <typename Dur> class Timer {
public:
  constexpr Timer() = default;

  constexpr Timer(Dur duration) : duration_(duration) {}

  void operator+=(Dur delta) { accumulator_ += delta; }

  template <typename Fn> void invoke_when_elapsed(Dur delta, Fn &&function) {
    accumulator_ += delta;
    if (has_elapsed()) {
      function();
    }
  }

  template <typename Fn> void invoke_periodically(Dur delta, Fn &&function) {
    accumulator_ += delta;
    while (has_elapsed()) {
      accumulator_ -= duration_;
      function();
    }
  }

  void set_duration(Dur duration) { duration_ = duration; }

  void reset() { accumulator_ = {}; }

  [[nodiscard]] auto has_elapsed() const -> bool {
    return accumulator_ >= duration_;
  }

  [[nodiscard]] auto duration() const -> Dur { return duration_; }

  [[nodiscard]] auto accumulator() const -> Dur { return accumulator_; }

private:
  Dur duration_{}, accumulator_{};
};
