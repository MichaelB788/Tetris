#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL_events.h>
#include "core/tetromino-controller.hpp"
#include "core/super-rotation-system.hpp"

struct EventHandler {
	void handleInput(SDL_Event& event, TetrominoController& controller);
};

#endif
