#pragma once
#include <limits>
#include <type_traits>

/// Small wrapper around an unsigned integer to represent circular values given
/// a range
template <typename T, T N>
  requires(std::is_unsigned_v<T> and N > 0 and
           N < std::numeric_limits<T>::max())
class CircularUint {
public:
  constexpr CircularUint(T init = 0) : val_(init % N) {}

  [[nodiscard]] operator T() const { return val_; }

  [[nodiscard]] auto incremented(const T addend = 1) const -> CircularUint {
    return (val_ + addend) % N;
  }

  [[nodiscard]] auto decremented(const T addend = 1) const -> CircularUint {
    return (val_ + N - addend) % N;
  }

  auto operator++() -> CircularUint & {
    val_ = incremented();
    return *this;
  }

  auto operator--() -> CircularUint & {
    val_ = decremented();
    return *this;
  }

  auto operator++(int) -> CircularUint {
    const auto ret = val_;
    operator++();
    return ret;
  }

  auto operator--(int) -> CircularUint {
    const auto ret = val_;
    operator--();
    return ret;
  }

private:
  T val_ = 0;
};
