#include "SevenBag.hpp"
#include "Piece.hpp"
#include <algorithm>
#include <random>

SevenBag::SevenBag(std::mt19937 &rng) : rng(rng) {
  std::shuffle(next.begin(), next.end(), rng);
  shuffle();
}

auto SevenBag::pop_next_type() -> Piece::Type {
  const auto next_type = current[read_idx++];
  if (read_idx == 7) {
    shuffle();
    read_idx = 0;
  }
  return next_type;
}

auto SevenBag::get_preview() const -> Preview {
  Preview preview{};
  for (size_t i = 0; i < preview.size(); ++i) {
    const auto j = read_idx + i;
    preview[i] = j < 7 ? current[j] : next[j - 7];
  }
  return preview;
}

void SevenBag::shuffle() {
  current = next;
  std::shuffle(next.begin(), next.end(), rng);

  if (current.back() == next.front())
    std::swap(next.front(), next[3]);
}
