#ifndef SUPER_ROTATION_SYSTEM_H
#define SUPER_ROTATION_SYSTEM_H
#include "core/tetromino.hpp"
#include "util/vector2.hpp"
#include <array>

class SuperRotationSystem {
public:
	SuperRotationSystem(Tetromino& tetromino);
	bool performRotationTests();

private:
	std::array<std::array<Vector2, 5>, 4> m_offsetData;
	Tetromino& m_tetromino; 
};

#endif
