#include "NextQueue.hpp"
#include "Tetromino.hpp"

void NextQueue::shuffle() {
  buffer_.clear();
  while (buffer_.size() < buffer_.max_size())
    push_random();
}

Tetromino::Type NextQueue::pop() {
  Tetromino::Type ret = buffer_.pop();
  push_random();
  return ret;
}

void NextQueue::push_random() {
  Tetromino::Type random = Tetromino::random_type();
  if (!buffer_.empty()) {
    while (random == buffer_.back())
      random = Tetromino::random_type();
  }
  buffer_.push(random);
}
