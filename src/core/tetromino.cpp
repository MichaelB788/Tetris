#include "core/tetromino.hpp"

namespace {
	Tetromino::Type getRandomType() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(0, 6);
		return Tetromino::Type(distrib(gen));
	}

	constexpr std::array<Vector2, 4> generateShape(Tetromino::Type type, Vector2 pivot) {
		switch(type) {
			case Tetromino::Type::I:
				return {
					pivot,
					pivot + Vector2::left() + Vector2::left(),
					pivot + Vector2::left(),
					pivot + Vector2::right()
				};
			case Tetromino::Type::O:
				return {
					pivot,
					pivot + Vector2::right(),
					pivot + Vector2::down(),
					pivot + Vector2::down() + Vector2::right()
				};
			case Tetromino::Type::T:
				return {
					pivot,
					pivot + Vector2::left(),
					pivot + Vector2::right(),
					pivot + Vector2::up()
				};
			case Tetromino::Type::Z:
				return {
					pivot,
					pivot + Vector2::up() + Vector2::left(),
					pivot + Vector2::up(),
					pivot + Vector2::right(),
				};
			case Tetromino::Type::S:
				return {
					pivot,
					pivot + Vector2::left(),
					pivot + Vector2::up(),
					pivot + Vector2::up() + Vector2::right()
				};
			case Tetromino::Type::J:
				return {
					pivot,
					pivot + Vector2::up() + Vector2::left(),
					pivot + Vector2::left(),
					pivot + Vector2::right(),
				};
			case Tetromino::Type::L:
				return {
					pivot,
					pivot + Vector2::up() + Vector2::right(),
					pivot + Vector2::right(),
					pivot + Vector2::left()
				};
			case Tetromino::Type::NONE: default:
				return {
					pivot, pivot, pivot, pivot
				};
		}
	}
}

Tetromino::Tetromino(Vector2 initialPos) {
	m_type = getRandomType(); 
	m_coordinates = generateShape(m_type, initialPos);
};

Tetromino::Tetromino(Tetromino::Type type, Vector2 initialPos) : m_type(type) {
	m_coordinates = generateShape(m_type, initialPos);
};

void Tetromino::operator=(const Tetromino& other) {
	m_coordinates = other.m_coordinates;
	m_type = other.m_type;
}

void Tetromino::shift(Vector2 translation) {
	for (auto& vec : m_coordinates) {
		vec += translation;
	}
}

void Tetromino::rotate(Vector2::Rotation rotation) {
	if (m_type != Tetromino::Type::O) {
		for (int i = 1; i < 4; i++) {
			m_coordinates[i].rotate90Degrees(rotation, m_coordinates[0]);
		}
	}
}
