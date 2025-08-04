#pragma once
#include <initializer_list>
#include <algorithm>

#include "GameConstants.hpp"
#include "Coordinate.hpp"

/**
 *	@breif: An Array2 object is a custom data structure which uses a one-dimensional array to represent a two-dimensional array.
 *
 *	@tparam: T Type of element.
 *	@tparam: N Number of elements.
 * */

template <typename T, size_t Rows, size_t Cols>
struct Array2 {
private:
	T m_Data[Rows * Cols];

public:
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using size_type = size_t;
	using different_type = ptrdiff_t;
	using pointer = T*;
	using const_pointer = const T*;

	constexpr size_t size() const { return Rows * Cols; }

	reference operator()(size_t row, size_t col) { return m_Data[row * Cols + col]; }
	const_reference operator()(size_t row, size_t col) const { return m_Data[row * Cols + col]; };

	Array2(std::initializer_list<T> args) { std::copy(args.begin(), args.end(), m_Data); }
};

/**
 *	@breif: Board is a 2D space which tracks the state of Tetromino.
 * */

class Board
{
private:
	Array2<Tile, 10, 20> m_State =
	{
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
		_, _, _, _, _, _, _, _, _, _,
	};

public:
	Board() = default;
};
