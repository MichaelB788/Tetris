#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL_events.h>
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include "core/matrix-operations.hpp"
#include "core/tetromino-operations.hpp"
#include "util/game-constants.hpp"


namespace event_handler {
	void handle(SDL_Event& event, Tetromino& actor, Matrix& matrix);

	namespace command {
		void move(Tetromino& actor, Direction dir, Matrix& scene);
		void rotate(Tetromino& actor, Matrix& scene);
		void drop(Tetromino& actor, Matrix& scene);
		void store(Tetromino& actor, Matrix& scene);
	}
}

#endif
