#ifndef TETRIS_H
#define TETRIS_H
#include <SDL2/SDL.h>
#include <array>
#include "core/tetromino.hpp"
#include "util/data-structures.hpp"
#include "util/game-constants.hpp"

class Tetris {
	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

		bool initSDL();
		void closeSDL();

	public:
		Tetris();
};

#endif
