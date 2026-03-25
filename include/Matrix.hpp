#pragma once
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>

template <size_t Col, size_t Row> struct Matrix {
public:
  std::array<std::array<uint8_t, Col>, Row> data{};

  [[nodiscard]] size_t row() const { return Row; }

  [[nodiscard]] size_t col() const { return Col; }

  [[nodiscard]] unsigned clear_lines();

  [[nodiscard]] bool is_row_empty(std::size_t row) const;

  [[nodiscard]] bool is_row_full(std::size_t row) const;

  void clear_row(std::size_t row);

  void move_row(std::size_t src, std::size_t dest);

  unsigned clear_full_rows();

  void drop_rows();
};
