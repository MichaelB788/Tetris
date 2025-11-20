#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

/// @note `colStart` should ideally be within 1 < `colStart` < WIDTH - 1
void fillRow(Matrix& matrix, unsigned int row, unsigned int colStart) {
	for (unsigned int col = colStart; col < Matrix::WIDTH - 1; col++) {
		matrix(col, row).setGround(Tetromino::Type::O);
	}
}

bool doesRowContainMatrixTile(Matrix& matrix, unsigned int row, Tile::State state) {
	for (unsigned int col = 1; col < Matrix::WIDTH - 1; col++) {
		if (matrix(col, row).state == state) return true;
	}
	return false;
}

TEST_CASE("Tetromino Operations", "[Matrix, Tetromino, unit]") 
{
	Matrix matrix;

	SECTION("Placing a Tetromino in a invalid position")
	{
		matrix.clearMatrix();
		Tetromino T {Tetromino::Type::T, {-999, -999}};
		REQUIRE(matrix.isTetrominoOutOfBounds(T));
		REQUIRE_THROWS(matrix.placeTetromino(T));
	}

	SECTION("Placing Tetromino")
	{
		matrix.clearMatrix();
		Tetromino O {Tetromino::Type::O, Matrix::TETROMINO_INITIAL_POS};
		REQUIRE_FALSE(matrix.isTetrominoOutOfBounds(O));
		REQUIRE_NOTHROW(matrix.placeTetromino(O));
	}

	SECTION("Grounding Tetromino")
	{
		matrix.clearMatrix();
		Tetromino O {Tetromino::Type::O, Matrix::TETROMINO_INITIAL_POS};
		REQUIRE_NOTHROW(matrix.lockDownTetromino(O));

		Tetromino T {Tetromino::Type::T, Matrix::TETROMINO_INITIAL_POS};
		REQUIRE(matrix.doesTetrominoCollideGround(T));
		REQUIRE(matrix.doesTetrominoCollideImpermeable(T));
	}

	SECTION("Removing Tetromino") {
		matrix.clearMatrix();
		Tetromino O {Tetromino::Type::O, Matrix::TETROMINO_INITIAL_POS};

		matrix.lockDownTetromino(O);
		CHECK(matrix.doesTetrominoCollideGround(O));
		matrix.removeTetromino(O);
		REQUIRE_FALSE(matrix.doesTetrominoCollideGround(O));
	}
}

TEST_CASE("Clearing and dropping full lines", "[Matrix, unit]") {
	Matrix matrix;

	// Convenience indices
	constexpr unsigned int INCOMPLETE_ROW_OFFSET = 5;
	constexpr unsigned int COMPLETED_ROW_OFFSET = 1;

	SECTION("One completed line below a incomplete line") {
		unsigned int completedRow = Matrix::HEIGHT - 1;
		unsigned int incompleteRow = completedRow - 1;
		fillRow(matrix, completedRow, COMPLETED_ROW_OFFSET);
		fillRow(matrix, incompleteRow, INCOMPLETE_ROW_OFFSET);

		int rowsCleared = matrix.clearAndDropLines();
		REQUIRE(rowsCleared == 1);
		CHECK(doesRowContainMatrixTile(matrix, incompleteRow, Tile::State::EMPTY));

		INFO("Expected ground tiles at: " << completedRow);
		REQUIRE(doesRowContainMatrixTile(matrix, completedRow, Tile::State::GROUND));
	}

	SECTION("One completed line below four incomplete lines") {
		matrix.clearMatrix();
		unsigned int completedRow = Matrix::HEIGHT - 1;
		std::array<unsigned int, 4> incompleteRows = {completedRow - 1, completedRow - 2, completedRow - 3, completedRow - 4};
		for (unsigned int i = 0; i < incompleteRows.size(); i++) {
			incompleteRows[i] = completedRow - (i + 1);
		}

		fillRow(matrix, completedRow, COMPLETED_ROW_OFFSET);
		for (const auto& row : incompleteRows) fillRow(matrix, row, INCOMPLETE_ROW_OFFSET);

		int rowsCleared = matrix.clearAndDropLines();
		REQUIRE(rowsCleared == 1);

		for (unsigned int i = 0; i < incompleteRows.size(); i++) {
			INFO("Expected ground tiles at row " << completedRow - i);
			REQUIRE(doesRowContainMatrixTile(matrix, completedRow - i, Tile::State::GROUND));
		}
	}

	SECTION("Four completed lines below a populated lines") {
		matrix.clearMatrix();
		std::array<unsigned int, 4> completedRows;
		std::array<unsigned int, 4> incompleteRows;
		for (unsigned int i = 0; i < completedRows.size(); i++) {
			completedRows[i] = Matrix::HEIGHT - (i + 1);
			incompleteRows[i] = Matrix::HEIGHT - (completedRows.size() + i + 1);
		}

		for (const auto& row : completedRows) fillRow(matrix, row, COMPLETED_ROW_OFFSET);
		for (const auto& row : incompleteRows) fillRow(matrix, row, INCOMPLETE_ROW_OFFSET);

		int rowsCleared = matrix.clearAndDropLines();
		REQUIRE(rowsCleared == completedRows.size());

		for (unsigned int i = 0; i < incompleteRows.size(); i++) {
			INFO("Expected ground tiles at row " << completedRows[i]);
			REQUIRE(doesRowContainMatrixTile(matrix, completedRows[i], Tile::State::GROUND));
		}
	}
}
