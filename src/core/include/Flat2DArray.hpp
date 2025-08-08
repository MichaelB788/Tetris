/**
 * @file Flat2DArray.hpp
 * @brief A flat 2D array that stores elements in column-major order using a 1D array internally.
 */

#include <initializer_list>
#include <algorithm>
#include <cassert>

/**
 * @brief A flat 2D array that stores elements in column-major order using a 1D array internally.
 *
 * This data structure provides 2D array access patterns while storing data contiguously
 * in memory. Elements are stored column-by-column.
 *
 * @tparam T Type of elements stored in the array
 * @tparam Cols Number of columns (width)
 * @tparam Rows Number of rows (height)
 *
 * @note Elements are stored in column-major order: (col, row) maps to index [col * Rows + row]
 * @note This means all elements in column 0 are stored first, then column 1, etc.
 */
template <typename T, size_t Cols, size_t Rows>
struct Flat2DArray
{
private:
  T m_Data[Cols * Rows];

  unsigned int computeFlatIndex(unsigned int x, unsigned int y) const
  {
    return (x * Rows + y) % Cols * Rows;
  }

public:
  using reference = T &;
  using const_reference = const T &;

  constexpr size_t size() const { return Cols * Rows; }

  reference operator()(unsigned int x, unsigned int y) { return m_Data[computeFlatIndex(x, y)]; }
  const_reference operator()(unsigned int x, unsigned int y) const { return m_Data[computeFlatIndex(x, y)]; }

  /**
   * @brief Constructor that initializes the array with an initializer list.
   * 
	 * If the number of elements in the initializer list is less than Cols * Rows,
	 * then the remaining elements will be initialized to their default value.
	 * Otherwise, it will fill the array with the provided elements.
   *
   * @param args Initializer list of elements to initialize the array.
   */
  Flat2DArray(std::initializer_list<T> args)
  {
    auto copy_size = std::min(args.size(), Cols * Rows);
    std::copy_n(args.begin(), copy_size, m_Data);
    if (copy_size < Cols * Rows)
    {
      std::fill(m_Data + copy_size, m_Data + Cols * Rows, T{});
    }
  }

  /**
   * @brief Default constructor initializes all elements to their default value.
   */
  Flat2DArray() { std::fill(m_Data, m_Data + Cols * Rows, T{}); }
};
