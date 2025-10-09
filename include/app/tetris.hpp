#ifndef TETRIS_H
#define TETRIS_H
#include <SDL2/SDL.h>
#include <array>
#include "util/vector2.hpp"
#include "util/game-constants.hpp"
#include "core/tetromino.hpp"
#include "core/matrix-operations.hpp"
#include "core/tetromino-operations.hpp"

class Tetris {
private:
  SDL_Window* m_window = nullptr;
  SDL_Renderer* m_renderer = nullptr;

  bool initSDL();
  void closeSDL();
  void update(Matrix& playfield, Tetromino& player);

public:
  Tetris();
};

#endif
