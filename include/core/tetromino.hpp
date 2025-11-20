#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <random>
#include "util/geometry.hpp"

class Tetromino {
public:
	enum class Type : uint8_t {
		I, O, T, Z, S, J, L, NONE
	};

	/// @brief Generates a Tetromino of a certain type centered at `initialPos`
	explicit Tetromino(Type type, Vector2 initialPos = {0, 0});

	void operator=(const Tetromino& other);

	Type getType() const { return type; } 

	/// @brief Generates a random type using the Mersene Twister pseudorandom algorithm
	static Type getRandomType(std::mt19937& gen); 

	uint8_t getCurrentRotationState() const { return rotationState; } 

	bool isNull() const { return type == Type::NONE; }

	void shift(Vector2 translation) {
		for (auto& vec : blocks) vec += translation;
	};

	void shift(int dx, int dy);

	void move(int x, int y);

	void move(Vector2 position) {
		move(position.x, position.y);
	};

	/// @brief Rotates this Tetromino 90 degrees clockwise or counterclockwise
	void rotate(Direction::Rotation direction);

	// Iterator
	using const_iterator = std::array<Vector2, 4>::const_iterator;

	const_iterator begin() const { return blocks.begin(); }
	const_iterator end() const { return blocks.end(); }

	const_iterator cbegin() const { return blocks.cbegin(); }
	const_iterator cend() const { return blocks.cend(); }

private:
	void generateShape(Type type, Vector2 pivot);
	void updateRotationState(Direction::Rotation direction);

private:
	std::array<Vector2, 4> blocks;
	Type type;
	uint8_t rotationState = 0;

	using v2 = Vector2;
	static constexpr std::array<std::array<v2, 4>, 8> TETROMINO_SHAPES = {{
		{ v2( 0,  0), v2(-1,  0), v2( 1,  0), v2( 2,  0) }, // I
		{ v2( 0,  0), v2( 1,  0), v2( 0,  1), v2( 1,  1) }, // O
		{ v2( 0,  0), v2(-1,  0), v2( 1,  0), v2( 0, -1) }, // T
		{ v2( 0,  0), v2(-1, -1), v2( 0, -1), v2( 1,  0) }, // Z
		{ v2( 0,  0), v2(-1,  0), v2( 0, -1), v2( 1, -1) }, // S
		{ v2( 0,  0), v2(-1, -1), v2(-1,  0), v2( 1,  0) }, // J
		{ v2( 0,  0), v2( 1, -1), v2( 1,  0), v2(-1,  0) }, // L
		{ v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0) }, // NONE
	}};
};

#endif
