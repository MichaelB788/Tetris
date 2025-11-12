#include "core/super-rotation-system.hpp"

const std::array<Vector2, 5>& SuperRotationSystem::getOffSetData(TetrominoType type, TetrominoRotation::State state) {
	if (type == TetrominoType::I) {
		return offsetDataI[state];
	} else {
		return offsetDataStandard[state];
	} 
}

//bool SuperRotationSystem::performTests(Compass::Axis before, Compass::Axis after) const {
//	for (int i = 0; i < rotatedOffsets.size(); i++) {
//		Vector2 translation = currentOffsets[i] - rotatedOffsets[i];
//		actor.shift(translation);
//		if (!scene.doesActorCollideImpermeable(actor)) break;
//		else actor.shift(-translation);
//	}
//}
