#include "util/vector2.hpp"

void Vector2::rotate90Degrees(bool clockwise, const Vector2& pivot) {
	if (pivot != *this) {
		const Vector2 translation = *this - pivot;
		const Vector2 rotated = clockwise ? Vector2(translation.y, -translation.x)
			: Vector2(-translation.y, translation.x);
		x = pivot.x + rotated.x;
		y = pivot.x + rotated.y;
	}
}
