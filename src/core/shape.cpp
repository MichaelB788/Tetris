#include "core/shape.hpp"

Shape::Shape(TetrominoType type) : m_type(type) {
	m_coordinates = Shape::Generator::getShape(type);
	m_pivot = Shape::Generator::pivot;
}

void Shape::shift(int dx, int dy) {
	const Vector2 translation = Vector2(dx, dy); 
	m_pivot + translation;
	for (auto& vec : m_coordinates) vec + translation;
}

void Shape::rotate90Degrees(bool clockwise) {
	for (auto &vec : m_coordinates) {
		Vector2 translation = vec - m_pivot;
		Vector2 rotated = clockwise ?
			Vector2(translation.y, -translation.x) : Vector2(-translation.y, translation.x);
		vec.x = m_pivot.x + rotated.x;
		vec.y = m_pivot.x + rotated.y;
	}
}

std::array<Vector2, 4> Shape::Generator::getShape(TetrominoType& type) {
	switch(type) {
		case TetrominoType::I:
			return {
				pivot - Vector2(1, 0),
				pivot - Vector2(2, 0),
				pivot,
				pivot + Vector2(1, 0)
			};
		case TetrominoType::O:
			return {
				pivot,
				pivot + Vector2(1, 0),
				pivot + Vector2(0, 1),
				pivot + Vector2(1, 1)
			};
		case TetrominoType::T:
			return {
				pivot - Vector2(1, 0),
				pivot,
				pivot + Vector2(1, 0),
				pivot + Vector2(0, 1)
			};
		case TetrominoType::Z:
			return {
				pivot - Vector2(1, 1),
				pivot - Vector2(0, 1),
				pivot,
				pivot + Vector2(1, 0),
			};
		case TetrominoType::S:
			return {
				pivot - Vector2(1, 0),
				pivot,
				pivot + Vector2(0, 1),
				pivot + Vector2(1, 1)
			};
		case TetrominoType::J:
			return {
				pivot - Vector2(1, 1),
				pivot - Vector2(1, 0),
				pivot,
				pivot + Vector2(1, 0),
			};
		case TetrominoType::L:
			return {
				pivot - Vector2(1, 0),
				pivot,
				pivot + Vector2(0, 1),
				pivot + Vector2(1, 1)
			};
		default:
			return {
				pivot, pivot, pivot, pivot
			};
	}
}
