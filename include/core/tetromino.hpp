#ifndef TETROMINO_OPERATIONS_H
#define TETROMINO_OPERATIONS_H
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

	void operator=(const Tetromino& other);
	
	inline const std::array<Vector2, 4>& coordinates() const { return m_coordinates; } 
	inline const TetrominoType type() const { return m_type; } 

	void shift(int dx, int dy);
	void shift(const Vector2& translation);

	void rotateClockwise();
	void rotateCounterclockwise();

private:
  static TetrominoType getRandomType();
	static std::array<Vector2, 4> generateShape(TetrominoType& type, Vector2& pivot);

private:
	std::array<Vector2, 4> m_coordinates;
	TetrominoType m_type;
	Vector2 m_pivot;
};

#endif
