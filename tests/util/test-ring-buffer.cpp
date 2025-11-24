#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include "util/ring-buffer.hpp"
#include "core/tetromino.hpp"

TEST_CASE("Initializer list", "[RingBuffer, unit]") {
	SECTION("Construction with initializer of VALID size") {
		auto createValidBuffer = []() { return RingBuffer<int, 5> {1, 2, 3, 4}; };
		REQUIRE_NOTHROW(createValidBuffer());
	}

	SECTION("Construction with initializer of INVALID size") {
		auto createValidBuffer = []() { return RingBuffer<int, 5> {1, 2, 3, 4, 5}; };
		REQUIRE_THROWS_AS(createValidBuffer(), std::length_error);
	}
}

TEST_CASE("Capacity", "[RingBuffer, unit]") {
	SECTION("Size of empty buffer") {
		RingBuffer<int, 20> buffer;

		REQUIRE(buffer.empty());
		REQUIRE(buffer.peek() == nullptr);
		REQUIRE(buffer.size() == 0);
		REQUIRE(buffer.max_size() == 19);
	}
}

TEST_CASE("Element Access", "[RingBuffer, unit]") {
	SECTION("Access first element of RingBuffer") {
		RingBuffer<int, 5> rb = {1, 2, 3, 4};
		int* ptr = rb.peek();
		const int* constPtr = rb.peek();
		REQUIRE(*ptr == *constPtr);
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
		REQUIRE(*rb.peek() == 4);
	}

	SECTION("Popping elements") {
		RingBuffer<int, 5> rb {1, 4, 5, 2};
		CHECK(*rb.peek() == 1);
		rb.pop();
		REQUIRE(*rb.peek() == 4);
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
		int loops = 0;
		for (const auto& tet : rb) {
			loops++;
			REQUIRE(tet.getType() == Tetromino::Type::I);
		}
		REQUIRE(loops == rb.size());
	}
}
