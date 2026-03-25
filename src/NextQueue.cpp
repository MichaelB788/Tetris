#include "NextQueue.hpp"
#include "Common.hpp"
#include "Tetromino.hpp"

NextQueue::NextQueue() {
  for (std::size_t i = 0; i < queue_.size(); ++i)
    push_non_repeating();
}

Tetromino NextQueue::pop_next() {
  Tetromino next = queue_[read];
  next.set_pos(Point(4, 2));
  read = (read + 1) % queue_.size();
  push_non_repeating();
  return next;
}

void NextQueue::push_non_repeating() {
  TetrominoType random = Tetromino::get_random_type();

  if (read != write) {
    const std::size_t prev = write == 0 ? queue_.size() - 1 : write - 1;

    do {
      random = Tetromino::get_random_type();
    } while (random == queue_[prev].type_());
  }

  queue_[write] = Tetromino(random, {.x = 0, .y = 0});
  write = (write + 1) % queue_.size();
}
