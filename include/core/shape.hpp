#ifndef TETROMINO_OPERATIONS_H
#define TETROMINO_OPERATIONS_H
#include <array>
#include "core/tile-state.hpp"
#include "util/vector2.hpp"

class Shape {
public:
	Shape(TetrominoType type, Vector2 pivot);
	
	inline const std::array<Vector2, 4>& coordinates() const { return m_coordinates; } 
	inline const TetrominoType type() const { return m_type; } 

	void shift(int dx, int dy);
	void shift(const Vector2& translation);

	virtual void rotateClockwise();
	virtual void rotateCounterclockwise();

protected:
	TetrominoType m_type;
	
private:
	std::array<Vector2, 4> m_coordinates;
	Vector2 m_pivot;
	class Generator;
};

struct Shape::Generator {
	static std::array<Vector2, 4> getShape(TetrominoType& type, Vector2& pivot);
};

#endif
