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

#ifndef MPBP_PACK_RECT_HPP
#define MPBP_PACK_RECT_HPP

#include <cmath>
#include <compare>
#include <cstddef>

namespace mpbp
{
  struct pack_rect
  {
    std::size_t x = 0;
    std::size_t y = 0;
    std::size_t z = 0;
    std::size_t width = 0;
    std::size_t height = 0;

    constexpr pack_rect() noexcept = default;

    constexpr pack_rect(const std::size_t x, const std::size_t y, const std::size_t z,
                        const std::size_t width, const std::size_t height) noexcept
        : x(x), y(y), z(z), width(width), height(height)
    {
    }

    constexpr std::size_t max_dimension() const noexcept { return std::max(this->width, this->height); }
    
    constexpr std::size_t far_x() const noexcept { return this->x + this->width - 1; }

    constexpr std::size_t far_y() const noexcept { return this->y + this->height - 1; }

    constexpr bool is_degenerate() const noexcept { return this->width == 0 || this->height == 0; }

    constexpr std::strong_ordering operator<=>(const mpbp::pack_rect& other) const noexcept
    {
      return this->max_dimension() <=> other.max_dimension();
    }

    constexpr bool fits(const mpbp::pack_rect& other) const noexcept
    {
      return (this->width >= other.width) && (this->height >= other.height);
    }
  };
}  // namespace mpbp

#endif