#include "core/NextQueue.hpp"
#include <algorithm>

void NextQueue::shuffle(std::mt19937 &rng) {
  Tetromino::Type last = buffer_.back();
  std::shuffle(buffer_.begin(), buffer_.end(), rng);
  if (buffer_.front() == last) {
    // Swap with any other element, since all elements are unique
    buffer_.front() = buffer_[3];
    buffer_[3] = last;
  }
  read_ = 0;
}
