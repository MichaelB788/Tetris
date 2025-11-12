#include "core/super-rotation-system.hpp"

void SuperRotationSystem::rotateActor(Tetromino& actor, Matrix& scene, Direction::Rotation direction) {
	scene.removeActor(actor);
	actor.rotate(direction);
	bool success;

	if (actor.type() == TetrominoType::I) {
		success = performOffsets(offsetDataI, actor, scene, rotationState.value(), rotationState.getStateAfterRotation(direction));
	} else {
		success = performOffsets(offsetDataStandard, actor, scene, rotationState.value(), rotationState.getStateAfterRotation(direction));
	}

	if (success) {
		rotationState.rotate(direction);
	} else {
		actor.rotate(Direction::getCounterRotation(direction));
	}
	scene.placeActor(actor);
}

bool SuperRotationSystem::performOffsets(const std::array<std::array<Vector2, 5>, 4>& offsets, Tetromino& actor, Matrix& scene, TetrominoRotation::State before, TetrominoRotation::State after) {
	for (int i = 0; i < offsets.size(); i++) {
		Vector2 translation = offsets[before][i] - offsets[after][i];
		actor.shift(translation);

		if (!scene.doesActorCollideImpermeable(actor)) return true;

		actor.shift(-translation);
	}
	return false;
}
