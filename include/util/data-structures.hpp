#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include <cstdint>
#include <array>

struct Vector2 {
	uint8_t x;
	uint8_t y;
};

class Matrix {
	private:
		const uint8_t width = 10, height = 24;
		std::array<uint8_t, 10 * 24> m_data;
		inline unsigned int computeFlatIndex(Vector2 coordinate) const { return coordinate.y * height + coordinate.x; }

	public:
		Matrix() = default;
		inline const uint8_t& operator()(Vector2 coordinate) { return m_data[computeFlatIndex(coordinate)]; }
};

#endif
