#ifndef TETROMINO_OPERATIONS_H
#define TETROMINO_OPERATIONS_H
#include <array>
#include "core/tile-state.hpp"
#include "util/vector2.hpp"

class Shape {
public:
	Shape(TetrominoType type);
	
	const std::array<Vector2, 4>& coordinates() const { return m_coordinates; } 
	inline TetrominoType type() { return m_type; }

	void shift(int dx, int dy);
	void rotate90Degrees(bool clockwise);

	class Generator;
	
private:
	TetrominoType m_type;
	std::array<Vector2, 4> m_coordinates;
	Vector2 m_pivot;
};

class Shape::Generator {
public:
	static constexpr Vector2 pivot = Vector2(0, 0);
	static std::array<Vector2, 4> getShape(TetrominoType& type);
};

#endif
