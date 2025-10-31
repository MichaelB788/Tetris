#ifndef TETRIS_H
#define TETRIS_H
#include <SDL2/SDL.h>
#include "core/tetromino.hpp"
#include "core/matrix.hpp"

class Tetris {
private:
  SDL_Window* m_window = nullptr;
  SDL_Renderer* m_renderer = nullptr;

  bool initSDL();
  void closeSDL();
  void update(Matrix& playfield, Tetromino& player);
	void gameLoop();

public:
  Tetris();
};

#endif
