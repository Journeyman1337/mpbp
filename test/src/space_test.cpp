// SPDX-FileCopyrightText: 2022 Daniel Valcour <fossweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#include <catch2/catch_all.hpp>
#include <mpbp/Rect.hpp>
#include <mpbp/Space.hpp>

SCENARIO("Properties are retrieved from a Space")
{
  GIVEN("A Space at (5, 10, 15) with a width of 20 and a height of 25")
  {
    mpbp::Space space(5, 10, 15, 20, 25);

    THEN("The getters return the correct values")
    {
      REQUIRE(!space.GetIsDegenerate());
      CHECK(space.GetLeftX() == 5);
      CHECK(space.GetTopY() == 10);
      CHECK(space.GetPage() == 15);
      CHECK(space.GetWidth() == 20);
      CHECK(space.GetHeight() == 25);
      CHECK(space.GetMaxDimension() == 25);
    }
  }
}

SCENARIO("Space degeneracy is determined")
{
  GIVEN("A Space with a width of 0 and a height of 1")
  {
    mpbp::Space space(0, 0, 0, 0, 1);

    THEN("The Space is degenerate") { REQUIRE(space.GetIsDegenerate()); }
  }

  GIVEN("A Space with a width of 1 and a height of 0")
  {
    mpbp::Space space(0, 0, 0, 1, 0);

    THEN("The Space is degenerate") { REQUIRE(space.GetIsDegenerate()); }
  }

  GIVEN("A Space with a width of -1 and a height of 1")
  {
    mpbp::Space space(0, 0, 0, -1, 1);

    THEN("The Space is degenerate") { REQUIRE(space.GetIsDegenerate()); }
  }

  GIVEN("A Space with a width of 1 and a height of -1")
  {
    mpbp::Space space(0, 0, 0, 1, -1);

    THEN("The Space is degenerate") { REQUIRE(space.GetIsDegenerate()); }
  }

  GIVEN("A Space with a width of 1 and a height of 1")
  {
    mpbp::Space space(0, 0, 0, 1, 1);

    THEN("The Space is not degenerate") { REQUIRE(!space.GetIsDegenerate()); }
  }
}

SCENARIO("A Space is compared with another Space")
{
  GIVEN("A Space named space_a with a width of 5 and a height of 10")
  {
    mpbp::Space space_a(0, 0, 0, 5, 10);

    GIVEN("A Space named space_b with a width of 10 and a height of 20")
    {
      mpbp::Space space_b(0, 0, 0, 10, 20);

      THEN("space_b is greater than space_a") { CHECK(space_b > space_a); }

      THEN("space_a is less than space_b") { CHECK(space_a < space_b); }
    }
  }
}

SCENARIO("Space max dimension is determined")
{
  GIVEN("A Space with a width of 5 and a height of 5")
  {
    mpbp::Space space(0, 0, 0, 5, 5);

    THEN("The max dimension of the Space is 5") { CHECK(space.GetMaxDimension() == 5); }
  }

  GIVEN("A Space with a width of 10 and a height of 20")
  {
    mpbp::Space space(0, 0, 0, 10, 20);

    THEN("The max dimension of the Space is 20") { CHECK(space.GetMaxDimension() == 20); }
  }
}

SCENARIO("Space is checked to see if it fits a Rect")
{
  GIVEN("A Space with a width of 5 and a height of 10")
  {
    mpbp::Space space(0, 0, 0, 5, 10);

    GIVEN("A Rect with a width of 1 and a height of 2")
    {
      mpbp::Rect rect(0, 1, 2);

      THEN("The Rect fits in the Space") { CHECK(space.Fits(rect)); }
    }

    GIVEN("A Rect with a width of 5 and a height of 10")
    {
      mpbp::Rect rect(0, 5, 10);

      THEN("The Rect fits in the Space") { CHECK(space.Fits(rect)); }
    }

    GIVEN("A Rect with a width of 5 and a height of 20")
    {
      mpbp::Rect rect(0, 10, 20);

      THEN("The Rect does not fit in the Space") { CHECK(!space.Fits(rect)); }
    }

    GIVEN("A Rect with a width of 20 and a height of 10")
    {
      mpbp::Rect rect(0, 20, 10);

      THEN("The Rect does not fit in the Space") { CHECK(!space.Fits(rect)); }
    }
  }
}