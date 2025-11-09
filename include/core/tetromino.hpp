#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <random>
#include "util/vector2.hpp"

class Tetromino {
public:
	/// @brief Types of Tetromino available for use. `Type` may be `NONE` in the case of unknown values.
	enum class Type : int8_t {
		NONE = -1, I, O, T, Z, S, J, L
	};

	/// @brief The four states of rotation a Tetromino takes
	enum RotationState {
		COUNTERCLOCKWISE = -1, ZERO = 0, CLOCKWISE = 1, TWO = 2
	};

	/// @brief Generates a Tetromino of a random type centered at `initialPos`
	Tetromino(Vector2 initialPos);
	/// @brief Generates a Tetromino of `Tetromino::Type type` centered at `initialPos`
	Tetromino(Tetromino::Type type, Vector2 initialPos);

	/// @return An immutable copy of this Tetromino's type
	inline Tetromino::Type type() const { return m_type; } 

	/// @brief Sets the coordinates and type of this Tetromino to `other`
	void operator=(const Tetromino& other);

	/// @brief Adds `translation` to each point in this Tetromino's coordinates
	void shift(Vector2 translation);
	inline void shift(int dx, int dy) { shift({dx, dy}); }

	/// @brief Rotates this Tetromino 90 degrees clockwise or counterclockwise
	void rotate(Vector2::Rotation rotation);

	// === Iterator ===
	using iterator = std::array<Vector2, 4>::iterator;
	using const_iterator = std::array<Vector2, 4>::const_iterator;

	iterator begin() { return m_coordinates.begin(); }
	iterator end() { return m_coordinates.end(); }

	const_iterator begin() const { return m_coordinates.begin(); }
	const_iterator end() const { return m_coordinates.end(); }

	const_iterator cbegin() const { return m_coordinates.cbegin(); }
	const_iterator cend() const { return m_coordinates.cend(); }

private:
	std::array<Vector2, 4> m_coordinates;
	Tetromino::Type m_type;
	int m_rotationState = 0;
};

struct SRS {
	std::array<Vector2, 5> Normal_Offset_Data = ;
	std::array<Vector2, 5> I_Offset_Data = ;
};

#endif
