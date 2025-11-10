#include "util/vector2.hpp"
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

/// @note `colStart` should ideally be within 1 < `colStart` < WIDTH - 1
void fillRow(Matrix& matrix, unsigned int row, unsigned int colStart) {
	for (unsigned int col = colStart; col < Matrix::WIDTH - 1; col++) {
		matrix(col, row).setGround(TetrominoType::O);
	}
}

bool doesRowContainMatrixTile(Matrix& matrix, unsigned int row, MatrixTile::State state) {
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
		Tetromino T = {TetrominoType::T, {-999, -999}};
		REQUIRE(matrix.isActorOutOfBounds(T));
		REQUIRE_THROWS(matrix.placeActor(T));
	}

	SECTION("Placing Tetromino")
	{
		matrix.clearMatrix();
		Tetromino O = {TetrominoType::O, Matrix::INITIAL_POS};
		REQUIRE_FALSE(matrix.isActorOutOfBounds(O));
		REQUIRE_NOTHROW(matrix.placeActor(O));
	}

	SECTION("Grounding Tetromino")
	{
		matrix.clearMatrix();
		Tetromino O = {TetrominoType::O, Matrix::INITIAL_POS};
		REQUIRE_NOTHROW(matrix.lockDownActor(O));

		Tetromino T = {TetrominoType::T, Matrix::INITIAL_POS};
		REQUIRE(matrix.doesActorCollideGround(T));
		REQUIRE(matrix.doesActorCollideImpermeable(T));
	}

	SECTION("Removing Tetromino") {
		matrix.clearMatrix();
		Tetromino O = {TetrominoType::O, Matrix::INITIAL_POS};

		matrix.lockDownActor(O);
		CHECK(matrix.doesActorCollideGround(O));
		matrix.removeActor(O);
		REQUIRE_FALSE(matrix.doesActorCollideGround(O));
	}

	SECTION("Calculating drop position on empty Matrix") {
		matrix.clearMatrix();
		Tetromino I = {TetrominoType::I, Matrix::INITIAL_POS};
		I = matrix.calculateDropPosition(I);
		REQUIRE_NOTHROW(matrix.placeActor(I));

		for (const auto& block : I) {
			REQUIRE(block.y == Matrix::HEIGHT - 1);
		}
	}

	SECTION("Calculating drop position on Matrix with preset ground tiles") {
		matrix.clearMatrix();
		unsigned int filledRow = Matrix::HEIGHT - 6;
		fillRow(matrix, filledRow, 1);

		Tetromino I = {TetrominoType::I, Matrix::INITIAL_POS};
		I = matrix.calculateDropPosition(I);

		for (const auto& block : I) {
			REQUIRE(block.y == filledRow - 1);
		}
	}
}

TEST_CASE("Clearing and dropping full lines", "[Matrix, unit]") {
	Matrix matrix;

	SECTION("One completed line below a populated line") {
		unsigned int filledRow = 3;
		unsigned int populatedRow = filledRow - 1;
		fillRow(matrix, filledRow, 1);
		fillRow(matrix, populatedRow, 5);

		int rowsCleared = matrix.clearAndDropLines();
		REQUIRE(rowsCleared == 1);
		REQUIRE(doesRowContainMatrixTile(matrix, HEIGHT - 1, MatrixTile::State::GROUND))
	}
}
