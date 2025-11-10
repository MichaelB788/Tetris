#include "util/vector2.hpp"

void Vector2::rotate90Degrees(Rotation rotation, const Vector2& pivot) {
	int dx = x - pivot.x;
	int dy = y - pivot.y;

	if (rotation == Rotation::CLOCKWISE) {
		x = pivot.x - dy;
		y = pivot.y + dx;
	} else {
		x = pivot.x + dy;
		y = pivot.y - dx;
	}
}
