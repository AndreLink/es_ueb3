#include "catch.hpp"
#include "PreAllocString.h"

TEST_CASE("String Tests", "[PreAllocString]") {

    SECTION("Basic Tests") {
        PreAllocString<20> pas;
        REQUIRE(pas.GetLength() == 0);
        REQUIRE(pas.SizeOf() == 20);
    }
}