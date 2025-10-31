#include "core/shape.hpp"
#include "core/tile-state.hpp"
#include "util/vector2.hpp"

Shape::Shape(TetrominoType type, Vector2 pivot) : m_type(type), m_pivot(pivot) {
	m_coordinates = Shape::Generator::getShape(m_type, m_pivot);
}

void Shape::shift(int dx, int dy) {
	const Vector2 translation{dx, dy}; 
	m_pivot + translation;
	for (auto& vec : m_coordinates) vec + translation;
}

void Shape::shift(const Vector2& translation) {
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
				pivot + Vector2::left + Vector2::left,
				pivot + Vector2::left,
				pivot,
				pivot + Vector2::right
			};
		case TetrominoType::O:
			return {
				pivot,
				pivot + Vector2::right,
				pivot + Vector2::down,
				pivot + Vector2::down + Vector2::right
			};
		case TetrominoType::T:
			return {
				pivot + Vector2::left,
				pivot,
				pivot + Vector2::right,
				pivot + Vector2::up
			};
		case TetrominoType::Z:
			return {
				pivot + Vector2::up + Vector2::left,
				pivot + Vector2::up,
				pivot,
				pivot + Vector2::right,
			};
		case TetrominoType::S:
			return {
				pivot + Vector2::left,
				pivot,
				pivot + Vector2::right,
				pivot + Vector2::up + Vector2::right
			};
		case TetrominoType::J:
			return {
				pivot + Vector2::up + Vector2::left,
				pivot + Vector2::up,
				pivot,
				pivot + Vector2::right,
			};
		case TetrominoType::L:
			return {
				pivot + Vector2::left,
				pivot,
				pivot + Vector2::right,
				pivot + Vector2::up + Vector2::right
			};
		default:
			return {
				pivot, pivot, pivot, pivot
			};
	}
}
