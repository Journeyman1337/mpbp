// SPDX-FileCopyrightText: 2022 Daniel Valcour <fossweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#include <catch2/catch_all.hpp>
#include <cstddef>
#include <functional>
#include <mpbp/Rect.hpp>

mpbp::Rect createRect(std::size_t identifier, int left_x, int top_y, int page, int width, int height)
{
  mpbp::Rect rect(identifier, width, height);
  rect.Place(left_x, top_y, page);
  return rect;
}

SCENARIO("The far coordinates of a Rect are determined")
{
  GIVEN("A Rect at (0, 0, 0) with a width of 5 and a height of 5")
  {
    auto rect = createRect(0, 0, 0, 0, 5, 5);

    THEN("The far coordinates are (4, 4)")
    {
      CHECK(rect.GetRightX() == 4);
      CHECK(rect.GetBottomY() == 4);
    }
  }

  GIVEN("A Rect at (10, 20, 30) with a width of 40 and a height of 50")
  {
    auto rect = createRect(0, 10, 20, 30, 40, 50);

    THEN("The far coordinates are (49, 69)")
    {
      CHECK(rect.GetRightX() == 49);
      CHECK(rect.GetBottomY() == 69);  // nice
    }
  }
}

SCENARIO("The position of a Rect is determined")
{
  GIVEN("A Rect that is not placed with a width of 32 and a height of 64.")
  {
    mpbp::Rect rect(0, 32, 64);

    THEN("The coordinates are (-1, -1, -1)")
    {
      CHECK(rect.GetLeftX() == -1);
      CHECK(rect.GetTopY() == -1);
      CHECK(rect.GetPage() == -1);
    }
  }

  GIVEN("A Rect with a width and height of 5")
  {
    mpbp::Rect rect(0, 5, 5);

    WHEN("The Rect is placed at (0, 0, 0)")
    {
      rect.Place(0, 0, 0);

      THEN("The Rect X Y and Z positions are (0, 0, 0)")
      {
        CHECK(rect.GetLeftX() == 0);
        CHECK(rect.GetTopY() == 0);
        CHECK(rect.GetPage() == 0);
      }
    }

    WHEN("The Rect is placed at (10, 20, 30)")
    {
      rect.Place(10, 20, 30);

      THEN("The Rect X Y and Z positons are (10, 20, 30)")
      {
        CHECK(rect.GetLeftX() == 10);
        CHECK(rect.GetTopY() == 20);
        CHECK(rect.GetPage() == 30);
      }
    }
  }
}

SCENARIO("Rect max dimension is determined")
{
  GIVEN("A Rect with a width of 5 and a height of 5")
  {
    auto rect = createRect(0, 0, 0, 0, 5, 5);

    THEN("The max dimension of the Rect is 5") { CHECK(rect.GetMaxDimension() == 5); }
  }

  GIVEN("A Rect with a width of 10 and a height of 20")
  {
    auto rect = createRect(0, 0, 0, 0, 10, 20);

    THEN("The max dimension of the Rect is 20") { CHECK(rect.GetMaxDimension() == 20); }
  }
}

SCENARIO("Rect degeneracy is determined")
{
  GIVEN("A Rect with a width of 0 and a height of 1")
  {
    auto rect = createRect(0, 0, 0, 0, 0, 1);

    THEN("The Rect is degenerate") { REQUIRE(rect.GetIsDegenerate()); }
  }

  GIVEN("A Rect with a width of 1 and a height of 0")
  {
    auto rect = createRect(0, 0, 0, 0, 1, 0);

    THEN("The Rect is degenerate") { REQUIRE(rect.GetIsDegenerate()); }
  }

  GIVEN("A Rect with a width of -1 and a height of 1")
  {
    auto rect = createRect(0, 0, 0, 0, -1, 1);

    THEN("The Rect is degenerate") { REQUIRE(rect.GetIsDegenerate()); }
  }

  GIVEN("A Rect with a width of 1 and a height of -1")
  {
    auto rect = createRect(0, 0, 0, 0, 1, -1);

    THEN("The Rect is degenerate") { REQUIRE(rect.GetIsDegenerate()); }
  }

  GIVEN("A Rect with a width of 1 and a height of 1")
  {
    auto rect = createRect(0, 0, 0, 0, 1, 1);

    THEN("The Rect is not degenerate") { REQUIRE(!rect.GetIsDegenerate()); }
  }
}

SCENARIO("A Rect is compared with another Rect")
{
  GIVEN("A Rect named rect_a with a width of 5 and a height of 10")
  {
    auto rect_a = createRect(0, 0, 0, 0, 5, 10);

    GIVEN("A Rect named rect_b with a width of 10 and a height of 20")
    {
      auto rect_b = createRect(0, 0, 0, 0, 10, 20);

      THEN("rect_b is greater than rect_a") { CHECK(rect_b > rect_a); }

      THEN("rect_a is less than rect_b") { CHECK(rect_a < rect_b); }
    }
  }
}
