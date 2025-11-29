#include <catch2/catch_test_macros.hpp>
#include <string>
#include "util/flat-array-map.hpp"

TEST_CASE("Lookup", "[FlatArrayMap, unit]") {
	SECTION("Contains and find lookups on const map") {
		const FlatArrayMap<std::string, int, 3> fam = { {"apple", 1}, {"cherry", 2}, {"banana", 3} };
		REQUIRE(fam.contains("apple"));
		const int* apple = fam.find("apple");
		const int* grape = fam.find("grape");
		REQUIRE(apple);
		REQUIRE_FALSE(grape);
	}

	SECTION("operator[] and other lookup functions on non-const map") {
		FlatArrayMap<std::string, int, 3> fam = { {"apple", 1}, {"cherry", 2}, {"banana", 3} };
		REQUIRE(fam["banana"] == 3);
		REQUIRE(fam["apple"] == fam.at("apple"));
		REQUIRE(fam["cherry"] == *fam.find("cherry"));
	}
}

TEST_CASE("Capacity", "[FlatArrayMap, unit]") {
	SECTION("Map with 2 key value pairs") {
		FlatArrayMap<std::string, int, 10> fam { {"apple", 4}, {"banana", 8} };
		REQUIRE_FALSE(fam.empty());
		REQUIRE(fam.size() == 2);
		REQUIRE(fam.max_size() == 10);
	}
}

TEST_CASE("Modifiers") {
	SECTION("Insertion") {
		FlatArrayMap<std::string, int, 3> fam;
		CHECK(fam.empty());
		fam.insert({"red", 3});
		fam.insert({"blue", 7});
		fam.insert({"green", 9});
		REQUIRE(fam.contains("red"));
		REQUIRE(fam.size() == fam.max_size());
	}

	SECTION("operator[] to create key value pairs") {
		FlatArrayMap<std::string, int, 3> fam;
		REQUIRE(fam["banana"] == 0);
		fam["grape"] = 3;
		REQUIRE(fam["grape"] == 3);
		CHECK(fam.size() == 2);
	}
}
