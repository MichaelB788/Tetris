#include <initializer_list>
#include <algorithm>
#include <cassert>

#include "Vector2.hpp"

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
struct Flat2DArray {
private:

	/**
	 * @brief Internal storage for the 2D array, represented as a flat 1D array.
	 */
	T m_Data[Cols * Rows];

	/**
	 * @brief Computes the flat index for a given 2D coordinate.
	 *
	 * @param coordinate The 2D coordinate to convert
	 * @return The computed flat index in the internal array
	 */
	unsigned int computeFlatIndex(const Vector2& coordinate) { return coordinate.x * Rows + coordinate.y; }

	bool isValidCoordinate(const Vector2& cooridnate) {
		size_t index = computeFlatIndex(coodinate);
		return index < size() && index >= 0;
	}

	bool isValidIndex(size_t index) { return index < size() && index >= 0; } 

public:
	using reference = T&;
	using const_reference = const T&;

	constexpr size_t size() const { return Cols * Rows; }

	/**
	 * @brief Accesses an element at the specified 2D coordinate.
	 *
	 * @param coordinate The 2D coordinate (x, y) to access
	 * @return Reference to the element at the specified coordinate
	 */
	reference operator()(const Vector2& coordinate) {
		assert(isValidCoordinate(coordinate) && "This coordinate is out of bounds!");
		return m_Data[computeFlatIndex(coordinate)];
	}

	/**
	 * @brief Accesses an element at the specified 2D coordinate (const version).
	 *
	 * @param coordinate The 2D coordinate (x, y) to access
	 * @return Const reference to the element at the specified coordinate
	 */
	const_reference operator()(const Vector2& coordinate) const {
		assert(isValidCoordinate(coordinate) && "This coordinate is out of bounds!");
		return m_Data[computeFlatIndex(coordinate)];
	};

	/**
	 * @brief Accesses an element at the specified index in the flat array.
	 *
	 * @param index The index to access (0 to Cols * Rows - 1)
	 * @return Reference to the element at the specified index
	 *
	 * @note This operator is provided for convenience, using 2D coordinates is preferred for clarity.
	 */
	reference operator[](unsigned int index) {
		assert(isValidIndext(index) && "This index is out of bounds!");
		return m_Data[index];
	}

	/**
	 * @brief Accesses an element at the specified index in the flat array (const version).
	 *
	 * @param index The index to access (0 to Cols * Rows - 1)
	 * @return Reference to the element at the specified index
	 *
	 * @note This operator is provided for convenience, using 2D coordinates is preferred for clarity.
	 */
	const_reference operator[](unsigned int index) const {
		assert(isValidIndext(index) && "This index is out of bounds!");
		return m_Data[index];
	};

	/**
	 * @brief Constructor that initializes the array with an initializer list.
	 *
	 * @param args Initializer list of elements to initialize the array.
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
	 */
	Flat2DArray() { std::fill(m_Data, m_Data + Cols * Rows, T()) };
};
