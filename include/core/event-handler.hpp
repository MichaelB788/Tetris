#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL_events.h>
#include "core/game-state.hpp"

struct EventHandler {
	static void handleInput(const SDL_Event& event, GameState& state);
};

#endif
