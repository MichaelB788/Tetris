#include <catch2/catch.hpp>
#include <array>
#include "util/game-constants.hpp"
#include "util/vector2.hpp"
#include "core/tetromino.hpp"
#include "core/tetromino-operations.hpp"

TEST_CASE("Moving Tetromino", "[TetrominoOperation, unit]") {
	SECTION("Moving an I piece LEFT") {
		Tetromino I = Tetromino(Tetromino::Type::I, Vector2(0, 0));
		std::array<Vector2, 4> before = I.m_coordinates;

		TetrominoOperation::move(I, Direction::LEFT);
		for (unsigned int i = 0; i < 4; i++) {
			REQUIRE(I.m_coordinates[i].x == before[i].x - 1);
			REQUIRE(I.m_coordinates[i].y == before[i].y);
		}
	}
	SECTION("Moving an I piece RIGHT") {
		Tetromino I = Tetromino(Tetromino::Type::I, Vector2(0, 0));
		std::array<Vector2, 4> before = I.m_coordinates;

		TetrominoOperation::move(I, Direction::RIGHT);
		for (unsigned int i = 0; i < 4; i++) {
			REQUIRE(I.m_coordinates[i].x == before[i].x + 1);
			REQUIRE(I.m_coordinates[i].y == before[i].y);
		}
	}
	SECTION("Moving an I piece DOWN") {
		Tetromino I = Tetromino(Tetromino::Type::I, Vector2(0, 0));
		std::array<Vector2, 4> before = I.m_coordinates;

		TetrominoOperation::move(I, Direction::DOWN);
		for (unsigned int i = 0; i < 4; i++) {
			REQUIRE(I.m_coordinates[i].x == before[i].x);
			REQUIRE(I.m_coordinates[i].y == before[i].y + 1);
		}
	}
}

TEST_CASE("Rotating a Tetromino 90 Degrees Counterclockwise", "[TetrominoOperation, unit]") {
	SECTION("Rotating an O piece should not be possible") {
		Tetromino O = Tetromino(Tetromino::Type::O, Vector2(0, 0));
		std::array<Vector2, 4> before = O.m_coordinates;

		TetrominoOperation::rotate(O);
		for (unsigned int i = 0; i < 4; i++) {
			REQUIRE(O.m_coordinates[i].x == before[i].x);
			REQUIRE(O.m_coordinates[i].y == before[i].y);
		}
	}
}
