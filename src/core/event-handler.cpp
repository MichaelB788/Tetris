#include "core/event-handler.hpp"

void event_handler::handle(SDL_Event& event, Tetromino& actor, Matrix& matrix)
{
	switch (event.key.keysym.sym)
	{
		// handle input
		case SDLK_LEFT:
		case SDLK_RIGHT:
		case SDLK_DOWN:
		case SDLK_UP:
		case SDLK_s:
		case SDLK_SPACE:
		default:
			break;
	}
}

void event_handler::command::move(Tetromino& actor, Direction dir, Matrix& scene) {
	std::array<Vector2, 4> previousCoordinates = actor.m_coordinates;
	tetromino_operation::move(actor, dir);

	if (matrix_operation::canPlaceTetromino(actor.m_coordinates, scene)) {
		matrix_operation::removeTetromino(previousCoordinates, scene);
		matrix_operation::placeTetromino(actor.m_coordinates, scene);
	} else {
		actor.m_coordinates = previousCoordinates;
	}
}

void event_handler::command::rotate(Tetromino& actor, Matrix& scene) {
	std::array<Vector2, 4> previousCoordinates = actor.m_coordinates;
	tetromino_operation::rotate(actor);

	// TODO: Implement RSS and come back to this
	if (matrix_operation::canPlaceTetromino(actor.m_coordinates, scene)) {
		matrix_operation::removeTetromino(previousCoordinates, scene);
		matrix_operation::placeTetromino(actor.m_coordinates, scene);
	} else {
		actor.m_coordinates = previousCoordinates;
	}
}

void event_handler::command::drop(Tetromino& actor, Matrix& scene) {
	while (matrix_operation::canPlaceTetromino(actor.m_coordinates, scene)) {
		tetromino_operation::move(actor, Direction::DOWN);
	}
	tetromino_operation::move(actor, Direction::UP);
	matrix_operation::placeTetromino(actor.m_coordinates, scene);
}
