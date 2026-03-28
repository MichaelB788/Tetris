#include "NextQueue.hpp"
#include "Tetromino.hpp"

void NextQueue::shuffle() {
  queue_.clear();
  while (queue_.size() < queue_.max_size())
    push_random();
}

Tetromino::Type NextQueue::pop() {
  Tetromino::Type ret = queue_.pop();
  push_random();
  return ret;
}

void NextQueue::push_random() {
  Tetromino::Type random;
  do {
    random = Tetromino::random_type();
  } while (random == queue_.back());
  queue_.push(random);
}
