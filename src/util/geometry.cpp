#include "util/geometry.hpp"

void Vector2::rotate90Degrees(Direction::Rotation rotation, const Vector2& pivot) {
	int dx = x - pivot.x;
	int dy = y - pivot.y;

	if (rotation == Direction::Rotation::CLOCKWISE) {
		x = pivot.x - dy;
		y = pivot.y + dx;
	} else {
		x = pivot.x + dy;
		y = pivot.y - dx;
	}
}
