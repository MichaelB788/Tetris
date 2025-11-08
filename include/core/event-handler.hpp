#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL_events.h>
#include "core/game-state.hpp"

class EventHandler {
public:
	EventHandler(GameState& gameState) : r_gameState(gameState) {};
	void handleInput(SDL_Event& event);

private:
	GameState& r_gameState;
};

#endif
