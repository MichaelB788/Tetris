#include "core/shape.hpp"
#include "core/tile-state.hpp"

Shape::Shape(TetrominoType type, Vector2 pivot) : m_type(type), m_pivot(pivot) {
	m_coordinates = Shape::Generator::getShape(m_type, m_pivot);
}

void Shape::shift(int dx, int dy) {
	const Vector2 translation = Vector2(dx, dy); 
	m_pivot + translation;
	for (auto& vec : m_coordinates) vec + translation;
}

void Shape::rotateClockwise() {
	for (auto &vec : m_coordinates) {
		vec.rotate90Degrees(true, m_pivot);
	}
}

void Shape::rotateCounterclockwise() {
	for (auto &vec : m_coordinates) {
		vec.rotate90Degrees(false, m_pivot);
	}
}

std::array<Vector2, 4> Shape::Generator::getShape(TetrominoType& type, Vector2& pivot) {
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
