#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <random>
#include "core/tile-state.hpp"
#include "util/vector2.hpp"

class Tetromino {
public:
	/// @brief Generates a Tetromino of a random type centered at the given position
	Tetromino(Vector2 initialPos);
	/// @brief Generates a Tetromino of a certain type at the given position
	Tetromino(TetrominoType type, Vector2 initialPos);

	using iterator = std::array<Vector2, 4>::iterator;
	using const_iterator = std::array<Vector2, 4>::const_iterator;

	iterator begin() { return m_coordinates.begin(); }
	iterator end() { return m_coordinates.end(); }

	const_iterator begin() const { return m_coordinates.begin(); }
	const_iterator end() const { return m_coordinates.end(); }

	const_iterator cbegin() const { return m_coordinates.cbegin(); }
	const_iterator cend() const { return m_coordinates.cend(); }

	inline const TetrominoType type() const { return m_type; } 
	/// @brief Get the pivot of the Tetromino, which acts as the center of rotatation
	const Vector2 pivot() const;

	void operator=(const Tetromino& other);

	/// @brief Moves the Tetromino given a translation vector
	void shift(const Vector2& translation);
	inline void shift(int dx, int dy) { shift({dx, dy}); }

	/// @brief Rotates this Tetromino 90 degrees clockwise or counterclockwise
	void rotate(Vector2::Rotation rotation);

private:
  static TetrominoType getRandomType();
	static constexpr std::array<Vector2, 4> generateShape(TetrominoType type, Vector2 pivot);

private:
	std::array<Vector2, 4> m_coordinates;
	TetrominoType m_type;
};

#endif
