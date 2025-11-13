#include "core/super-rotation-system.hpp"

namespace {
	bool performOffsetTests(const std::array<std::array<Vector2, 5>, 4>& offsets, Tetromino& actor, const Matrix& scene, const uint8_t stateBefore, const uint8_t stateAfter) {
		for (int i = 0; i < offsets.size(); i++) {
			Vector2 translation = offsets[stateBefore][i] - offsets[stateAfter][i];
			actor.shift(translation);

			if (!scene.doesTetrominoCollideImpermeable(actor)) return true;

			actor.shift(-translation);
		}
		return false;
	}
}

void SuperRotationSystem::rotateTetromino(Tetromino& actor, Matrix& scene, Direction::Rotation direction) {
	scene.removeTetromino(actor);
	uint8_t originalRotationState = actor.getCurrentRotationState();
	actor.rotate(direction);

	bool success;
	if (actor.getType() == TetrominoType::I) {
		success = performOffsetTests(offsetDataI, actor, scene, originalRotationState, actor.getCurrentRotationState());
	} else {
		success = performOffsetTests(offsetDataStandard, actor, scene, originalRotationState, actor.getCurrentRotationState());
	}

	if (!success) {
		actor.rotate(Direction::getCounterRotation(direction));
	}
	scene.placeTetromino(actor);
}
