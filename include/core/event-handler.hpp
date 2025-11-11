#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL_events.h>
#include "core/game-state.hpp"

class EventHandler {
public:
	EventHandler() {};
	void handleInput(SDL_Event& event, GameState& gameState);

private:
};

#endif
