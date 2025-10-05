#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include "util/data-structures.hpp"

/* *
 * @breif Tetromino structs contain data, namely: color and an array of tiles representing the shape.
 * */
struct Tetromino {
	enum class Type : uint8_t { I, O, T, Z, S, J, L };
	enum class Color : uint8_t { LIGHT_BLUE, ORANGE, BLUE, GREEN, RED, PURPLE, YELLOW, WHITE };
	enum class Role : uint8_t { NONE = 0, ACTIVE, GROUNDED, GHOST };

	Type m_type;
	Color m_color;
	Role m_role;
	std::array<Vector2, 4> m_position;
	Tetromino(Type type, Color color, Role role) : m_type(type), m_color(color), m_role(role) {};
};

#endif
