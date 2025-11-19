#ifndef COLOR_H
#define COLOR_H
#include <SDL2/SDL_pixels.h>
#include "core/matrix-tile.hpp"
#include "core/tetromino-type.hpp"

namespace Color {
	enum class ID {
		WHITE,
		GRAY,
		BLUE,
		RED,
		GREEN,
		CYAN,
		ORANGE,
		MAGENTA,
		YELLOW,
		BLACK
	};

	const SDL_Color getColor(const Color::ID color);

	const SDL_Color getTetrominoColor(const TetrominoType type);

	const SDL_Color getMatrixTileColor(const MatrixTile tile);
};

#endif
