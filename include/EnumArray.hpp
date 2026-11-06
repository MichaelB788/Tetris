#include <array>
#include <cstddef>

template <typename T, size_t N, typename Enum>
struct EnumArray : public std::array<T, N> {
  using Base = std::array<T, N>;

  [[nodiscard]] auto operator[](Enum enum_idx) -> T & {
    return Base::operator[](static_cast<size_t>(enum_idx));
  }

  [[nodiscard]] auto operator[](Enum enum_idx) const -> const T & {
    return Base::operator[](static_cast<size_t>(enum_idx));
  }
};
