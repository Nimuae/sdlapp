#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test Test") {
	std::cout << "Hello!" << std::endl;
	REQUIRE(true);
}