#pragma once
#include <array>
#include <cassert>
#include <cstddef>
#include <iterator>

/// Circular buffer capable of storing N - 1 elements
template <typename T, size_t N> class CircularBuffer {
public:
  template <typename... E>
  constexpr CircularBuffer(E... elements) : buffer_{elements...} {}

  [[nodiscard]] size_t size() const { return (write_ - read_) + N; }

  [[nodiscard]] size_t max_size() const { return N - 1; }

  [[nodiscard]] const T &front() const { return buffer_[read_]; }

  [[nodiscard]] const T &back() const { return buffer_[write_]; }

  [[nodiscard]] const T &pop();

  void push(const T &element);

  void clear() { read_ = write_ = 0; }

public:
  class Iterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    Iterator(T *base, size_t i) : base_(base), idx_(i) {}

    T &operator*() { return base_[idx_]; }
    T &operator->() { return &base_[idx_]; }

    Iterator &operator++() {
      idx_ = (idx_ + 1) % N;
      return *this;
    }

    Iterator operator++(int) {
      Iterator ret = *this;
      operator++();
      return ret;
    }

    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.base_ == b.base_ && a.idx_ == b.idx_;
    }
    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return !(a == b);
    }

  private:
    T *base_ = nullptr;
    size_t idx_ = 0;
  };

  [[nodiscard]] Iterator begin() { return Iterator(buffer_.data(), read_); }
  [[nodiscard]] Iterator end() { return Iterator(buffer_.data(), write_); }

  [[nodiscard]] const Iterator begin() const {
    return Iterator(buffer_.data(), read_);
  }
  [[nodiscard]] const Iterator end() const {
    return Iterator(buffer_.data(), write_);
  }

private:
  size_t read_ = 0;
  size_t write_ = 0;
  std::array<T, N> buffer_{};
};

template <typename T, size_t N> const T &CircularBuffer<T, N>::pop() {
  if (read_ == write_) {
    assert(false && "Could not pop any element, Circular Buffer is empty.");
    return buffer_[read_];
  }

  const T &ret = buffer_[read_];
  read_ = (read_ + 1) % N;
  return ret;
}

template <typename T, size_t N>
void CircularBuffer<T, N>::push(const T &element) {
  if ((write_ + 1) % N == read_) {
    assert(false &&
           "Could not push element, Circular Buffer is at max capacity");
    return;
  }

  buffer_[write_] = element;
  write_ = (write_ + 1) % N;
}
