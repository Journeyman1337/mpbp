/*
    MIT License
    Copyright (c) 2021 Daniel Valcour
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <catch2/catch_all.hpp>
#include <mpbp/Packer.hpp>
#include <mpbp/Rect.hpp>
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
      if (a_i != b_i && recta.GetZ() == rectb.GetZ())
      {
        if (recta.GetX() < rectb.GetFarX() && recta.GetFarX() > rectb.GetX() &&
            recta.GetY() < rectb.GetFarY() && recta.GetFarY() > rectb.GetY())
        {
          return false;
        }
      }
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
