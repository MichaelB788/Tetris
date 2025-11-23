#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include "util/ring-buffer.hpp"

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
		REQUIRE(buffer.size() == 0);
	}
}

TEST_CASE("Element Access", "[RingBuffer, unit]") {
	SECTION("Access first element of RingBuffer") {
		RingBuffer<int, 5> rb = {1, 2, 3, 4};
		int& ref = rb.peek();
		const int& constRef = rb.peek();
		REQUIRE(ref == constRef);
	}
}

TEST_CASE("Modifiers", "[RingBuffer, unit]") {
	SECTION("")
}
