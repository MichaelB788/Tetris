#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <random>
#include "util/vector2.hpp"
#include "util/cyclic-int8_t.hpp"
#include "core/tetromino-type.hpp"

class Tetromino {
public:
	/// @brief Generates a Tetromino of a random type centered at `initialPos`
	Tetromino(Vector2 initialPos);
	/// @brief Generates a Tetromino of `Tetromino::Type type` centered at `initialPos`
	Tetromino(TetrominoType type, Vector2 initialPos);

	inline TetrominoType type() const { return m_type; } 
	inline CyclicInt8_t rotationState() const { return m_rotationState; } 

	/// @brief Adds `translation` to each point in this Tetromino's coordinates
	void shift(Vector2 translation);
	inline void shift(int dx, int dy) { shift({dx, dy}); }

	/// @brief Rotates this Tetromino 90 degrees clockwise or counterclockwise
	void rotate(Vector2::Rotation rotation);

	// === Iterator ===
	using iterator = std::array<Vector2, 4>::iterator;
	using const_iterator = std::array<Vector2, 4>::const_iterator;

	iterator begin() { return m_coordinates.begin(); }
	iterator end() { return m_coordinates.end(); }

	const_iterator begin() const { return m_coordinates.begin(); }
	const_iterator end() const { return m_coordinates.end(); }

	const_iterator cbegin() const { return m_coordinates.cbegin(); }
	const_iterator cend() const { return m_coordinates.cend(); }

private:
	std::array<Vector2, 4> m_coordinates;
	TetrominoType m_type;
	CyclicInt8_t m_rotationState = {-1, 4};
};

#endif
