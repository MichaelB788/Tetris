#include "core/tetromino-controller.hpp"
#include <array>

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
	TetrominoRotation::State currentState = actor.rotationState();
	actor.rotate(rotationDirection);

	if (scene.doesActorCollideImpermeable(actor)) {
		const std::array<Vector2, 5>& currentOffsets = SRS.getOffSetData(actor.type(), currentState);
		const std::array<Vector2, 5>& rotatedOffsets = SRS.getOffSetData(actor.type(), actor.rotationState());
		for (int i = 0; i < rotatedOffsets.size(); i++) {
			Vector2 translation = currentOffsets[i] - rotatedOffsets[i];
			actor.shift(translation);
			if (!scene.doesActorCollideImpermeable(actor)) break;
			else actor.shift(-translation);
		}
	}

	scene.placeActor(actor);
}
