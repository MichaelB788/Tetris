#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include <cstdint>
#include <array>
#include "util/game-constants.hpp"

/**
 * @brief Stores two (x, y) coordinates.
 * @note x and y values are uint8_t and can go up to 255, which is more than enough for our 10 x 24 matrix.
 **/
struct Vector2 {
	uint8_t x;
	uint8_t y;
};

/// @brief A 10 x 24 matrix. Data stored within the Matrix are of TileState. 
class TetrisMatrix {
	private:
		std::array<TileState, 10 * 24> m_data {};
		inline const unsigned int computeFlatIndex(Vector2 coordinate) const { return coordinate.y * HEIGHT + coordinate.x; }
		inline const unsigned int computeFlatIndex(uint8_t x, uint8_t y) const { return y * HEIGHT + x; }

	public:
    const uint8_t WIDTH = 10, HEIGHT = 24; 
		TetrisMatrix() = default;

		inline TileState& operator() (uint8_t x, uint8_t y) { return m_data[computeFlatIndex(x, y)]; }
		inline const TileState& operator() (uint8_t x, uint8_t y) const { return m_data[computeFlatIndex(x, y)]; }
		inline TileState& operator() (Vector2 coordinate) { return m_data[computeFlatIndex(coordinate)]; }
		inline const TileState& operator() (Vector2 coordinate) const { return m_data[computeFlatIndex(coordinate)]; }
};

#endif
