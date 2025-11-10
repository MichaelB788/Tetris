#ifndef SUPER_ROTATION_SYSTEM_H
#define SUPER_ROTATION_SYSTEM_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include "util/vector2.hpp"
#include <array>

class SuperRotationSystem {
public:
	using v2 = Vector2;
	SuperRotationSystem(Tetromino& tetromino, Matrix& matrix)
		: r_tetromino(tetromino),
			r_matrix(matrix),
			m_offsetDataStandard({{
					{ v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0), },
					{ v2( 0,  0), v2( 1,  0), v2( 1,  1), v2( 0, -2), v2( 1, -2), },
					{ v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0), },
					{ v2( 0,  0), v2(-1,  0), v2(-1,  1), v2( 0, -2), v2(-1, -2), },
					}}),
			m_offsetDataI({{
					{ v2( 0,  0), v2(-1,  0), v2( 2,  0), v2(-1,  0), v2( 2,  0), },
					{ v2(-1,  0), v2( 0,  0), v2( 0,  0), v2( 0, -1), v2( 1, +2), },
					{ v2(-1, -1), v2( 1, -1), v2(-2, -1), v2( 1,  0), v2(-2,  0), },
					{ v2( 0,  1), v2(-1,  0), v2(-1,  1), v2( 0, -2), v2( 0,  0), },
					}})
	{};

	bool performRotationTests();

private:
	std::array<std::array<Vector2, 5>, 4> m_offsetDataStandard;
	std::array<std::array<Vector2, 5>, 4> m_offsetDataI;
	Tetromino& r_tetromino; 
	Matrix& r_matrix;
};

#endif
