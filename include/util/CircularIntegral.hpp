#pragma once
#include <cstddef>
#include <type_traits>

/// Small wrapper around an unsigned integer to represent circular values given
/// a range
template <typename T, size_t N>
  requires(std::is_integral_v<T>)
class CircularIntegral {
public:
  CircularIntegral(T init = 0) : val(init) {}

  void operator++() { val = (val + 1) % N; }

  auto operator++(int) -> T {
    const auto ret = val;
    operator++();
    return ret;
  }

  void operator--() { val = (val + N - 1) % N; }

  auto operator--(int) -> T {
    const auto ret = val;
    operator--();
    return ret;
  }

  [[nodiscard]] auto value() const -> T { return val; }

private:
  T val = 0;
};
