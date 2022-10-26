// SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#include <catch2/catch_all.hpp>
#include <mpbp/Packer.hpp>
#include <mpbp/Rect.hpp>
#include <mpbp/Space.hpp>
#include <vector>
#include <cstddef>

bool noRectIntersect(std::vector<mpbp::Rect>& rects)
{
  for (std::size_t a_i = 0; a_i < rects.size(); a_i++)
  {
    auto& recta = rects[a_i];
    for (std::size_t b_i = 0; b_i < rects.size(); b_i++)
    {
      auto& rectb = rects[b_i];
      if (a_i != b_i && recta.GetPage() == rectb.GetPage())
      {
        if (recta.GetLeftX() < rectb.GetRightX() && recta.GetRightX() > rectb.GetLeftX() &&
            recta.GetTopY() < rectb.GetBottomY() && recta.GetBottomY() > rectb.GetTopY())
        {
          return false;
        }
      }
    }
  }
  return true;
}

bool noUnplacedRect(std::vector<mpbp::Rect>& rects)
{
  for(const auto& rect : rects)
  {
    if (rect.GetLeftX() < 0 || rect.GetRightX() < 0 || rect.GetPage() < 0)
    {
      return false;
    }
  }
  return true;
}

bool noInvalidSpace(std::vector<mpbp::Space> spaces)
{
  for (const auto& space : spaces)
  {
    if (space.GetLeftX() < 0 || space.GetTopY() < 0 || space.GetPage() < 0 || space.GetWidth() <= 0 || space.GetHeight() <= 0)
    {
      return false;
    }
  }
  return true;
}

SCENARIO("Packer is used to bin pack")
{
  GIVEN("A Packer with max dimensions (512, 512)")
  {
    mpbp::Packer packer(512, 512);

    GIVEN("A packable vector of Rect")
    {
      std::vector<mpbp::Rect> rects = {
          mpbp::Rect(0, 1, 1),    mpbp::Rect(0, 1, 1),     mpbp::Rect(0, 1, 1),
          mpbp::Rect(0, 1, 1),    mpbp::Rect(0, 1, 1),     mpbp::Rect(0, 5, 5),
          mpbp::Rect(0, 5, 5),    mpbp::Rect(0, 5, 5),     mpbp::Rect(0, 5, 5),
          mpbp::Rect(0, 25, 125), mpbp::Rect(0, 125, 52),  mpbp::Rect(0, 11, 5),
          mpbp::Rect(0, 48, 48),  mpbp::Rect(0, 48, 48),   mpbp::Rect(0, 48, 48),
          mpbp::Rect(0, 48, 48),  mpbp::Rect(0, 48, 48),   mpbp::Rect(0, 48, 48),
          mpbp::Rect(0, 48, 48),  mpbp::Rect(0, 48, 48),   mpbp::Rect(0, 48, 48),
          mpbp::Rect(0, 48, 48),  mpbp::Rect(0, 48, 48),   mpbp::Rect(0, 48, 48),
          mpbp::Rect(0, 48, 48),  mpbp::Rect(0, 512, 512), mpbp::Rect(0, 512, 1),
          mpbp::Rect(0, 1, 512)};

      WHEN("The vector of Rect is packed with the Packer")
      {
        packer.Pack(rects);

        THEN("No Rect intersect") { CHECK(noRectIntersect(rects)); }
        THEN("All rects are placed") { CHECK(noUnplacedRect(rects)); }
        THEN("No spaces are invalid") { CHECK(noInvalidSpace(packer.GetSpaces())); }
      }

      WHEN("The vector of Rect is cut in half and packed online")
      {
        auto half_way = rects.size() / 2;
        std::span<mpbp::Rect> spana(&rects.front(), half_way);
        std::span<mpbp::Rect> spanb(&rects.front() + half_way, rects.size() - half_way);
        packer.Pack(spana);
        packer.Pack(spanb);

        THEN("No Rect intersect") { CHECK(noRectIntersect(rects)); }
        THEN("All rects are placed") { CHECK(noUnplacedRect(rects)); }
        THEN("No spaces are invalid") { CHECK(noInvalidSpace(packer.GetSpaces())); }
      }
    }

    GIVEN("A vector of Rect where one is larger than the Packer max dimensions")
    {
      std::vector<mpbp::Rect> rects = {mpbp::Rect(0, 1, 1), mpbp::Rect(0, 1, 1),
                                       mpbp::Rect(0, 1, 1), mpbp::Rect(0, 1, 1),
                                       mpbp::Rect(0, 1, 513)};

      THEN("The Packer throws an exception on packing the Rect vector")
      {
        CHECK_THROWS(packer.Pack(rects));
      }
    }

    GIVEN("A vector of Rect where one is degenerate")
    {
      std::vector<mpbp::Rect> rects = {mpbp::Rect(0, 1, 1), mpbp::Rect(0, 1, 1),
                                       mpbp::Rect(0, 1, 1), mpbp::Rect(0, 1, 1),
                                       mpbp::Rect(0, 1, 0)};

      THEN("The Packer throws an exception on packing the Rect vector")
      {
        CHECK_THROWS(packer.Pack(rects));
      }
    }
  }
}
