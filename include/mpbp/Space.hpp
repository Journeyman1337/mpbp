// SPDX-FileCopyrightText: 2022 Daniel Valcour <fossweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef MPBP_SPACE_HPP
#define MPBP_SPACE_HPP

#include <compare>

namespace mpbp
{
  struct Rect;

  class Space
  {
   private:
    int max_dimension = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    int width = 0;
    int height = 0;

   public:
    constexpr Space() noexcept = default;
    Space(int x, int y, int z, int width, int height) noexcept;

    int GetX() const noexcept;
    int GetY() const noexcept;
    int GetZ() const noexcept;
    int GetWidth() const noexcept;
    int GetHeight() const noexcept;
    int GetMaxDimension() const noexcept;
    bool GetIsDegenerate() const noexcept;
    std::strong_ordering operator<=>(const mpbp::Space& other) const noexcept;
    bool Fits(const mpbp::Rect& rect) const noexcept;
  };
}  // namespace mpbp

#endif