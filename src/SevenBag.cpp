#include "SevenBag.hpp"
#include "Tetromino.hpp"
#include <algorithm>

SevenBag::SevenBag(std::mt19937 &rng) {
  std::ranges::shuffle(next_bag_, rng);
  shuffle(rng);
}

void SevenBag::shuffle(std::mt19937 &rng) {
  read_ = 0;
  curr_bag_ = next_bag_;
  std::ranges::shuffle(next_bag_, rng);

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

auto SevenBag::preview() const -> Preview {
  Preview view{};
  auto i = read_;
  for (auto &type : view) {
    type = i < curr_bag_.size() ? curr_bag_[i++]
                                : next_bag_[i++ - curr_bag_.size()];
  }
  return view;
}
