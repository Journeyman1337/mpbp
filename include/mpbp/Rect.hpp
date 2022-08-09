// SPDX-FileCopyrightText: 2022 Daniel Valcour <fossweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef MPBP_PACK_RECT_HPP
#define MPBP_PACK_RECT_HPP

#include <cmath>
#include <compare>
#include <cstddef>

namespace mpbp
{
  class Rect
  {
   private:
    std::size_t identifier = 0;
    int x = -1;
    int y = -1;
    int z = -1;
    int width = 0;
    int height = 0;

   public:
    constexpr Rect() noexcept = default;
    Rect(std::size_t identifier, int width, int height) noexcept;

    void Place(int x, int y, int z) noexcept;
    int GetX() const noexcept;
    int GetY() const noexcept;
    int GetZ() const noexcept;
    int GetFarX() const noexcept;
    int GetFarY() const noexcept;
    int GetWidth() const noexcept;
    int GetHeight() const noexcept;
    std::size_t GetIdentifier() const noexcept;
    int GetMaxDimension() const noexcept;
    bool GetIsDegenerate() const noexcept;
    std::strong_ordering operator<=>(const mpbp::Rect& other) const noexcept;
  };
}  // namespace mpbp

#endif