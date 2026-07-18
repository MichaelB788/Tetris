#include "SevenBag.hpp"
#include "Tetromino.hpp"
#include <algorithm>

SevenBag::SevenBag(std::mt19937 &rng) : rng(rng), curr_bag() {
  using enum Tetromino::Type;
  curr_bag = next_bag = {I, O, T, S, Z, J, L};
  std::ranges::shuffle(next_bag, rng);
  shuffle();
}

void SevenBag::shuffle() {
  read = 0;
  curr_bag = next_bag;
  std::ranges::shuffle(next_bag, rng);

  if (curr_bag.back() == next_bag[0]) {
    // Swap with any other element, since all elements are unique
    const auto temp = next_bag[0];
    next_bag[0] = next_bag[3];
    next_bag[3] = temp;
  }
}

auto SevenBag::pop() -> Tetromino::Type {
  const auto next_type_ = curr_bag[read++];
  if (read == curr_bag.size()) {
    shuffle();
  }
  return next_type_;
}

auto SevenBag::peek() const -> Tetromino::Type { return curr_bag[read]; }

auto SevenBag::get_preview() const -> Preview {
  Preview preview{};
  auto i = read;
  for (auto &type : preview) {
    if (i < curr_bag.size()) {
      type = curr_bag[i++];
    } else {
      type = next_bag[i - curr_bag.size()];
      ++i;
    }
  }
  return preview;
}
