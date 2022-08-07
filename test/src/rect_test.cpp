#include <catch2/catch_all.hpp>
#include <mpbp/Rect.hpp>
#include <functional>
#include <cstddef>

mpbp::Rect createRect(std::size_t identifier, int x, int y, int z, int width, int height)
{
    mpbp::Rect rect(identifier, width, height);
    rect.Place(x, y, z);
    return rect;
}

SCENARIO("The far coordinates of a Rect are determined")
{
    GIVEN("A Rect at (0, 0, 0) with a width of 5 and a height of 5")
    {
        auto rect = createRect(0, 0, 0, 0, 5, 5);

        THEN("The far coordinates are (4, 4)")
        {
            CHECK(rect.GetFarX() == 4);
            CHECK(rect.GetFarY() == 4);
        }
    }

    GIVEN("A Rect at (10, 20, 30) with a width of 40 and a height of 50")
    {
        auto rect = createRect(0, 10, 20, 30, 40, 50);

        THEN("The far coordinates are (49, 69)")
        {
            CHECK(rect.GetFarX() == 49);
            CHECK(rect.GetFarY() == 69); // nice
        }
    }
}

SCENARIO("A Rect is placed at a position and page")
{
    GIVEN("A Rect with a width and height of 5")
    {
        mpbp::Rect rect(0, 5, 5);

        WHEN("The Rect is placed at (0, 0, 0)")
        {
            rect.Place(0, 0, 0);

            THEN("The Rect X Y and Z positions are (0, 0, 0)")
            {
                CHECK(rect.GetX() == 0);
                CHECK(rect.GetY() == 0);
                CHECK(rect.GetZ() == 0);
            }
        }

        WHEN("The Rect is placed at (10, 20, 30)")
        {
            rect.Place(10, 20, 30);

            THEN("The Rect X Y and Z positons are (10, 20, 30)")
            {
                CHECK(rect.GetX() == 10);
                CHECK(rect.GetY() == 20);
                CHECK(rect.GetZ() == 30);
            }
        }
    }
}

SCENARIO("Rect max dimension is determined")
{
    GIVEN("A Rect with a width of 5 and a height of 5")
    {
        auto rect = createRect(0, 0, 0, 0, 5, 5);

        THEN("The max dimension of the Rect is 5")
        {
            CHECK(rect.GetMaxDimension() == 5);
        }
    }

    GIVEN("A Rect with a width of 10 and a height of 20")
    {
        auto rect = createRect(0, 0, 0, 0, 10, 20);

        THEN("The max dimension of the Rect is 20")
        {
            CHECK(rect.GetMaxDimension() == 20);
        }
    }
}

SCENARIO("Rect degeneracy is determined")
{
    GIVEN("A Rect with a width of 0 and a height of 1")
    {
        auto rect = createRect(0, 0, 0, 0, 0, 1);

        THEN("The Rect is degenerate")
        {
            REQUIRE(rect.GetIsDegenerate());
        }
    }

    GIVEN("A Rect with a width of 1 and a height of 0")
    {
        auto rect = createRect(0, 0, 0, 0, 1, 0);

        THEN("The Rect is degenerate")
        {
            REQUIRE(rect.GetIsDegenerate());
        }
    }

    GIVEN("A Rect with a width of -1 and a height of 1")
    {
        auto rect = createRect(0, 0, 0, 0, -1, 1);

        THEN("The Rect is degenerate")
        {
            REQUIRE(rect.GetIsDegenerate());
        }
    }

    GIVEN("A Rect with a width of 1 and a height of -1")
    {
        auto rect = createRect(0, 0, 0, 0, 1, -1);

        THEN("The Rect is degenerate")
        {
            REQUIRE(rect.GetIsDegenerate());
        }
    }

    GIVEN("A Rect with a width of 1 and a height of 1")
    {
        auto rect = createRect(0, 0, 0, 0, 1, 1);

        THEN("The Rect is not degenerate")
        {
            REQUIRE(!rect.GetIsDegenerate());
        }
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

            THEN("rect_b is greater than rect_a")
            {
                CHECK(rect_b > rect_a);
            }

            THEN("rect_a is less than rect_b")
            {
                CHECK(rect_a < rect_b);
            }
        }
    }
}
