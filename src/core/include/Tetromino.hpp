#ifndef TETROMINO_H
#define TETROMINO_H

#include "Coordinate.hpp"
#include "GameConstants.hpp"
#include <array>
#include <cctype>
#include <cstdlib>
#include <ctime>

class Tetromino
{
	private:
		std::array<Point, 4> m_position;
		Tile m_type,
				 m_next,
				 m_stored = NIL;

	public:
		Tetromino(Tile type);

		std::array<Point, 4> translate(Direction dir);
		std::array<Point, 4> rotate();
		void swap();
		void store();
		void draw();

		void setPosition(std::array<Point, 4> newPosition)
		{ m_position = newPosition; }

		Tile type() { return m_type; }
		Tile next() { return m_next; }
		Tile stored() { return m_stored; }

		std::array<Point, 4> position() { return m_position; }
};

#endif
