#ifndef TETROMINO_H
#define TETROMINO_H
#include <cstdint>
#include <array>

/* *
 * @breif Tetromino structs contain data, namely: coordinates (in index form), color, and type
 * */
struct Tetromino {
	enum class Type : uint8_t { I, O, T, Z, S, J, L };
	enum class Role : uint8_t { NONE = 0, ACTIVE, GROUNDED, GHOST };
	enum class Color : uint8_t { LIGHT_BLUE, ORANGE, BLUE, GREEN, RED, PURPLE, YELLOW, WHITE };

	Type type;
	Role role;
	Color color;
	std::array<uint8_t, 4> indexes;
};

#endif
