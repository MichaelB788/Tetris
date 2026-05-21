#include "core/SevenBag.hpp"
#include "core/Tetromino.hpp"
#include <algorithm>
#include <cstddef>

SevenBag::SevenBag(std::mt19937 &rng) {
  std::shuffle(next_bag_.begin(), next_bag_.end(), rng);
  shuffle(rng);
}

void SevenBag::shuffle(std::mt19937 &rng) {
  read_ = 0;
  curr_bag_ = next_bag_;
  std::shuffle(next_bag_.begin(), next_bag_.end(), rng);

  if (curr_bag_.back() == next_bag_[0]) {
    // Swap with any other element, since all elements are unique
    const auto temp = next_bag_[0];
    next_bag_[0] = next_bag_[3];
    next_bag_[3] = temp;
  }
}

auto SevenBag::pop(std::mt19937 &rng) -> Tetromino {
  const auto next_type_ = curr_bag_[read_++];
  if (read_ == curr_bag_.size()) {
    shuffle(rng);
  }
  return Tetromino{.type = next_type_};
}

auto SevenBag::preview() const -> SevenBag::Preview {
  SevenBag::Preview view{};
  auto next_index = read_;
  for (size_t i = 0; i < view.size(); ++i) {
    view[i] = next_index < curr_bag_.size()
                  ? curr_bag_[next_index++]
                  : next_bag_[next_index++ - curr_bag_.size()];
  }
  return view;
}
