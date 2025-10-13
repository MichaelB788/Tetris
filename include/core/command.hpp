#ifndef COMMAND_H
#define COMMAND_H
#include <array>
#include "core/matrix.hpp"
#include "core/matrix-operations.hpp"
#include "core/tetromino.hpp"
#include "core/tetromino-operations.hpp"
#include "util/game-constants.hpp"

namespace Command {
	void move(Tetromino& actor, Direction dir, Matrix& scene);
	void rotate(Tetromino& actor, Matrix& scene);
	void drop(Tetromino& actor, Matrix& scene);
	void store(Tetromino& actor, Matrix& scene);
}

#endif
