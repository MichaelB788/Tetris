#include "util/vector2.hpp"

void Vector2::rotate90Degrees(Rotation rotation, Vector2& target, const Vector2& pivot) {
	const Vector2 translation = target - pivot;
	const Vector2 rotated = rotation == Rotation::CLOCKWISE ?
			Vector2(translation.y, -translation.x)
		: Vector2(-translation.y, translation.x);
	target.x = pivot.x + rotated.x;
	target.y = pivot.x + rotated.y;
}
