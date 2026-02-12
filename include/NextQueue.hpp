#ifndef TETRIS_NEXT_QUEUE
#define TETRIS_NEXT_QUEUE
#include "Tetromino.hpp"
#include <array>

class NextQueue {
public:
  NextQueue();

  Tetromino pop_next();

  struct const_iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    const_iterator(const Tetromino *base, std::size_t indx, std::size_t size)
        : base_(base), indx_(indx), size_(size) {}

    const Tetromino &operator*() const { return base_[indx_]; }
    const Tetromino *operator->() const { return &base_[indx_]; }

    const_iterator &operator++() {
      indx_ = (indx_ + 1) % size_;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp = *this;
      operator++();
      return tmp;
    }

    friend bool operator==(const_iterator &a, const_iterator &b) {
      return a.base_ == b.base_ && a.indx_ == b.indx_ && a.size_ == b.size_;
    }
    friend bool operator!=(const_iterator &a, const_iterator &b) {
      return !(a == b);
    }

  private:
    const Tetromino *base_;
    std::size_t indx_;
    std::size_t size_;
  };

  const_iterator begin() const {
    return const_iterator(queue_.data(), read, queue_.size());
  }

  const_iterator end() const {
    return const_iterator(queue_.data(), write, queue_.size());
  }

private:
  void push_non_repeating();

  std::array<Tetromino, 5> queue_{};

  std::size_t read = 0, write = queue_.size() - 1;
};

#endif
