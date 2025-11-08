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

	void operator=(const Tetromino& other);
	
	inline const std::array<Vector2, 4>& coordinates() const { return m_coordinates; } 
	inline const TetrominoType type() const { return m_type; } 

	void shift(const Vector2& translation);
	inline void shift(int dx, int dy) { shift({dx, dy}); }

	void rotate(Vector2::Rotation rotation);

  static TetrominoType getRandomType();

private:
	static std::array<Vector2, 4> generateShape(TetrominoType& type, Vector2& pivot);

private:
	std::array<Vector2, 4> m_coordinates;
	TetrominoType m_type;
};

#endif
