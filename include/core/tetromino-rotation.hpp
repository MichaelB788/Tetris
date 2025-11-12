#ifndef COMPASS_H
#define COMPASS_H
#include "util/direction.hpp"
#include <stdint.h>
#include <array>

/// @brief Tracks the rotational state a Tetromino is in.
class TetrominoRotation {
public:
	enum State : uint8_t {
		ZERO = 0, CLOCKWISE = 1, TWO = 2, COUNTERCLOCKWISE = 3
	};

	void rotate(Direction::Rotation direction) {
		if (direction == Direction::Rotation::CLOCKWISE) {
			index = (index + 1) % 4;
		} else {
			index = (index - 1 < 0) ? 3 : index - 1;
		}
	}

	State getStateAfterRotation(Direction::Rotation direction) const {
		if (direction == Direction::Rotation::CLOCKWISE) {
			return states[(index + 1) % 4];
		} else {
			return states[(index - 1 < 0) ? 3 : index - 1];
		}
	}

	State value() const { return states[index]; }

private:
	std::array<State, 4> states = { State::ZERO, State::CLOCKWISE, State::TWO, State::COUNTERCLOCKWISE };
	int index = 0;
};

#endif
