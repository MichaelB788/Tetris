#ifndef TETROMINO_OPERATIONS_H
#define TETROMINO_OPERATIONS_H
#include <array>
#include "core/tile-state.hpp"
#include "util/vector2.hpp"

class Shape {
public:
	Shape();
	Vector2& pivot(); 
	std::array<Vector2, 4>& cooridnates(); 
	void shift(int dx, int dy);

private:
	class TetrominoLibrary;
	
private:
	std::array<Vector2, 4> m_coordinates;
	Vector2 m_pivot;
};

class Shape::TetrominoLibrary {
public:
	TetrominoLibrary() = default;
	static std::array<Vector2, 4> generate(TetrominoType& type);

private:
	static constexpr Vector2 pivot = Vector2(0, 0);

	std::array<Vector2, 4> I = {
		pivot,
		pivot - Vector2(1, 0),
		pivot - Vector2(2, 0),
		pivot + Vector2(1, 0)
	};

	std::array<Vector2, 4> O = {
		pivot,
		pivot + Vector2(1, 0),
		pivot + Vector2(0, 1),
		pivot + Vector2(1, 1)
	};

	std::array<Vector2, 4> T = {
		pivot,
		pivot - Vector2(1, 0),
		pivot + Vector2(1, 0),
		pivot + Vector2(0, 1)
	};

	std::array<Vector2, 4> Z = {
		pivot,
		pivot - Vector2(1, 0),
		pivot + Vector2(0, 1),
		pivot + Vector2(1, 1)
	};
};

#endif
