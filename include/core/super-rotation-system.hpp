#ifndef SUPER_ROTATION_SYSTEM_H
#define SUPER_ROTATION_SYSTEM_H
#include "util/vector2.hpp"
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include <array>

class SuperRotationSystem {
	public:
		SuperRotationSystem() {}
		const std::array<Vector2, 5>& getOffSetData(TetrominoType type, TetrominoRotation::State state);
		//bool performTests() const;

	private:

		using v2 = Vector2;
		const std::array<std::array<Vector2, 5>, 4> offsetDataStandard {{
			{ v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0) },
			{ v2( 0,  0), v2( 1,  0), v2( 1,  1), v2( 0, -2), v2( 1, -2) },
			{ v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0) },
			{ v2( 0,  0), v2(-1,  0), v2(-1,  1), v2( 0, -2), v2(-1, -2) }
		}};
		const std::array<std::array<Vector2, 5>, 4> offsetDataI {{
			{ v2( 0,  0), v2(-1,  0), v2( 2,  0), v2(-1,  0), v2( 2,  0), },
			{ v2(-1,  0), v2( 0,  0), v2( 0,  0), v2( 0, -1), v2( 1, +2), },
			{ v2(-1, -1), v2( 1, -1), v2(-2, -1), v2( 1,  0), v2(-2,  0), },
			{ v2( 0,  1), v2(-1,  0), v2(-1,  1), v2( 0, -2), v2( 0,  0), }
		}};
};

#endif
