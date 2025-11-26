#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "util/ring-buffer.hpp"
#include "core/tetromino.hpp"

TEST_CASE("Capacity", "[RingBuffer, unit]") {
	SECTION("Size of empty buffer") {
		RingBuffer<int, 20> buffer;

		REQUIRE(buffer.empty());
		REQUIRE(buffer.size() == 0);
		REQUIRE(buffer.max_size() == 19);
	}
}

TEST_CASE("Element Access", "[RingBuffer, unit]") {
	SECTION("Access first element of RingBuffer") {
		RingBuffer<int, 5> rb = {1, 2, 3, 4};
		int ref = rb.peek();
		const int constRef = rb.peek();
		REQUIRE(ref == constRef);
	}
}

TEST_CASE("Modifiers", "[RingBuffer, unit]") {
	SECTION("Pushing elements") {
		RingBuffer<int, 5> rb;
		CHECK(rb.empty());
		rb.push(4);
		rb.push(235);
		REQUIRE_FALSE(rb.empty());

		REQUIRE(rb.size() > 0);
		REQUIRE(rb.peek() == 4);
	}

	SECTION("Popping elements") {
		RingBuffer<int, 5> rb {1, 4, 5, 2};
		CHECK(rb.peek() == 1);
		rb.pop();
		REQUIRE(rb.peek() == 4);
	}

	SECTION("Popping elements until nothing is left") {
		RingBuffer<int, 5> rb {1, 4, 5, 2};
		while (!rb.empty()) rb.pop();
		REQUIRE(rb.empty());
	}
}

TEST_CASE("Iterator", "[RingBuffer, unit]") {
	SECTION("Iterating through Tetromino ring buffer") {
		RingBuffer<Tetromino, 5> rb = { Tetromino(Tetromino::Type::I), Tetromino(Tetromino::Type::I), Tetromino(Tetromino::Type::I) };
		CHECK(rb.size() == 3);
		int loops = 0;
		for (const auto& tet : rb) {
			loops++;
			REQUIRE(tet.getType() == Tetromino::Type::I);
		}
		REQUIRE(loops == rb.size());
	}
}
