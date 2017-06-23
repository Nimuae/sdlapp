#include <iostream>
#include <thread>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Vector2D.h"

TEST_CASE("Vector Tests") {
	SECTION("Vector Addition") {
		Vector2D v1 = Vector2D(0, 0);
		Vector2D v2 = Vector2D(1, 1);
		REQUIRE((v1 + v2) == Vector2D(1, 1));
	}

	SECTION("Vector Subtraction") {
		Vector2D v1 = Vector2D(0, 0);
		Vector2D v2 = Vector2D(1, 1);
		REQUIRE((v1 - v2) == Vector2D(-1, -1));
	}

	SECTION("Vector Equality") {
		Vector2D v1 = Vector2D(1, 1);
		Vector2D v2 = Vector2D(1, 1);
		REQUIRE(v1 == v2);
	}

	SECTION("Vector Unequality") {
		Vector2D v1 = Vector2D(0, 1);
		Vector2D v2 = Vector2D(1, 1);
		REQUIRE(v1 != v2);
	}

	SECTION("Vector Unequality") {
		Vector2D v1 = Vector2D(0, 1);
		Vector2D v2 = Vector2D(1, 1);
		REQUIRE(v1 != v2);
	}

	SECTION("Dot Product") {
		Vector2D v1 = Vector2D(0, 1);
		Vector2D v2 = Vector2D(1, 1);
		REQUIRE(v1.dot(v2) == 1);

		v1 = Vector2D(2, 3);
		v2 = Vector2D(3, 4);
		REQUIRE(v1.dot(v2) == 18);

		v1 = Vector2D(-2, 3);
		v2 = Vector2D(3, -4);
		REQUIRE(v1.dot(v2) == -18);

		v1 = Vector2D(-2, 0);
		v2 = Vector2D(0, -2);
		REQUIRE(v1.dot(v2) == 0);
	}

	SECTION("Orthogonal Vector") {
		Vector2D v1 = Vector2D(0, 1);
		REQUIRE(v1.getOrtho() == Vector2D(-1, 0));

		v1 = Vector2D(-5, 10);
		REQUIRE(v1.getOrtho() == Vector2D(-10, -5));
	}
}

TEST_CASE("Line Tests") {
	SECTION("Line Intersection - Point") {
		Line2D line1 = Line2D(Vector2D(0, 0), Vector2D(0, 1));
		Line2D line2 = Line2D(Vector2D(0, 2), Vector2D(1, 0));

		Vector2D point = line1.getIntersectPoint(line2);

		REQUIRE(point == Vector2D(0, 2));
	}

	SECTION("Line Intersection - Point") {
		Line2D line = Line2D(Vector2D(0, 0), Vector2D(0, 1));
		Vector2D point = Vector2D(3, 3);

		REQUIRE(line.distanceToPoint(point) == 3);
	}
}