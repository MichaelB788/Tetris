#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "Flat2DArray.hpp"

TEST_CASE("Flat2DArray implementation test", "[unit]")
{
  Flat2DArray<int, 2, 2> arr;
  REQUIRE(arr.size() == 4);
}