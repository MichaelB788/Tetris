#include "core/tetromino-controller.hpp"

void TetrominoController::moveActor(const Matrix& scene, Direction::Horizontal direction) {
	Vector2 translation = Vector2::getHorizontal(direction); 
	actor.shift(translation);

	if (scene.doesActorCollideImpermeable(actor)) {
		actor.shift(-translation);
	}
}

void TetrominoController::moveActorDown(Matrix& scene) {
	actor.shift(Vector2::down());

	if (scene.doesActorCollideGround(actor)) {
		actor.shift(Vector2::up());
		scene.lockDownActor(actor);
	}
}

void TetrominoController::dropActor(Matrix& scene) {
	scene.removeActor(actor);
	actor = scene.calculateDropPosition(actor);
	scene.lockDownActor(actor);
}

void TetrominoController::rotateActor(const Matrix& scene, Direction::Rotation rotationDirection, const std::array<Vector2, 5>& offsets) {
	actor.rotate(rotationDirection);

	// This needs to be refactored...
	const Tetromino temp = actor;
	if (scene.doesActorCollideImpermeable(actor)) {

		Vector2 wallKick = actor.center().x > Matrix::WIDTH / 2
			? Vector2::left()
			: Vector2::right();
		actor.shift(wallKick);

		if (scene.doesActorCollideImpermeable(actor)) {
			actor.shift(-wallKick);
			int tries = 0;
			for (const auto& offset : SRS::offset_data(actor)) {
				actor.shift(offset);
				if (scene.doesActorCollideImpermeable(actor)) {
					actor.shift(-offset);
					++tries;
				} else {
					break;
				}
			}
			if (tries == 5) {
				actor = temp;
			}
		}
	}
}
