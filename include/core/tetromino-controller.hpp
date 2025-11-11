#ifndef TETROMINO_CONTROLLER_H
#define TETROMINO_CONTROLLER_H
#include "util/vector2.hpp"
#include "core/tetromino.hpp"
#include "core/matrix.hpp"
#include "core/super-rotation-system.hpp"

class TetrominoController {
public:
	TetrominoController(Tetromino& actor) : actor(actor) {};
	
	void moveActor(const Matrix& scene, Direction::Horizontal direction);
	void moveActorDown(Matrix& scene);
	void dropActor(Matrix& scene);
	void rotateActor(const Matrix& scene, Direction::Rotation rotationDirection, const std::array<Vector2, 5>& offsets);

private:
	Tetromino& actor;
};

#endif
