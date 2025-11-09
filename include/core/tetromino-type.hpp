#ifndef TETROMINO_TYPE_H
#define TETROMINO_TYPE_H
#include <stdint.h>

/// @brief Types of Tetromino available for use. `Type` may be `NONE` in the case of unknown values.
enum class TetrominoType : int8_t {
	NONE = -1, I, O, T, Z, S, J, L
};

#endif
