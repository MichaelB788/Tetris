#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL_events.h>
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

class EventHandler {
public:
	EventHandler(Matrix& matrix, Tetromino& tetromino)
		: m_scene(matrix),
			m_actor(tetromino)
	{}; 

	void handle(SDL_Event& event);

private:
	Matrix& m_scene;
	Tetromino& m_actor;
};

namespace command {
	void move(Tetromino& actor, Direction dir, Matrix& scene);
	void rotate(Tetromino& actor, Matrix& scene);
	void drop(Tetromino& actor, Matrix& scene);
	void store(Tetromino& actor, Matrix& scene);
}

#endif
