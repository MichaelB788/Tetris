#include "core/tetromino-controller.hpp"

void TetrominoController::moveActor(Direction::Horizontal direction) {
	scene.removeActor(actor);
	Vector2 translation = Vector2::getHorizontal(direction); 
	actor.shift(translation);

	if (scene.doesActorCollideImpermeable(actor)) {
		actor.shift(-translation);
	}
	scene.placeActor(actor);
}

void TetrominoController::moveActorDown() {
	scene.removeActor(actor);
	actor.shift(Vector2::down());

	if (scene.doesActorCollideGround(actor)) {
		actor.shift(Vector2::up());
		scene.lockDownActor(actor);
	}
	scene.placeActor(actor);
}

void TetrominoController::dropActor() {
	scene.removeActor(actor);
	actor = scene.calculateDropPosition(actor);
	scene.lockDownActor(actor);
}

void TetrominoController::rotateActor(Direction::Rotation rotationDirection) {
	scene.removeActor(actor);
	actor.rotate(rotationDirection);

	if (scene.doesActorCollideImpermeable(actor)) {
		for (const auto& offset : SRS::offset_data(actor)) {
			actor.shift(-offset);
			if (!scene.doesActorCollideImpermeable(actor)) break;
		}
	}

	scene.placeActor(actor);
}
