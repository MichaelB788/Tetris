#include <initializer_list>
#include <algorithm>

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
 * @note Elements are stored in column-major order: [row][col] maps to index [col * Rows + row]
 * @note This means all elements in column 0 are stored first, then column 1, etc.
 */
template <typename T, size_t Cols, size_t Rows>
struct Flat2DArray {
private:
	T m_Data[Cols * Rows];

public:
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using size_type = size_t;
	using different_type = ptrdiff_t;
	using pointer = T*;
	using const_pointer = const T*;

	constexpr size_t size() const { return Cols * Rows; }

	reference operator()(size_t col, size_t row) { return m_Data[col * Rows + row]; }
	const_reference operator()(size_t col, size_t row) const { return m_Data[col * Rows + row]; };

	/**
	* @brief If the initializer_list is of the same size as the array, copy the elements.
	* Otherwise, copy as many elements as possible and fill the rest with default values.
	* 
	* Complexity: O(n) where n is the size of the initializer_list or the array size, whichever is smaller.
	*/
	Flat2DArray(std::initializer_list<T> args)
	{
		if (args.size() == Cols * Rows) std::copy(args.begin(), args.end(), m_Data);
		else {
			std::fill(m_Data, m_Data + Cols * Rows, T());
			std::copy_n(args.begin(), std::min(args.size(), Cols * Rows), m_Data);
		}
	}

	/**
	* @brief Default constructor initializes all elements to their default value.
	* 
	* Complexity: O(n) where n is the number of elements in the array (Cols * Rows).
	*/
	Flat2DArray() { std::fill(m_Data, m_Data + Cols * Rows, T()) };
};
