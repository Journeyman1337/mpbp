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

#ifndef MPBP_INPUT_RECT_HPP
#define MPBP_INPUT_RECT_HPP

#include <cstddef>
#include <mpbp/pack_rect.hpp>

namespace mpbp
{
  struct input_rect : public mpbp::pack_rect
  {
    std::size_t identifier = 0;

    using mpbp::pack_rect::pack_rect;

    constexpr input_rect() noexcept = default;

    constexpr input_rect(const std::size_t identifier, const std::size_t width,
                         const std::size_t height) noexcept
        : identifier(identifier), mpbp::pack_rect(0, 0, 0, width, height)
    {
    }

    constexpr void Place(const std::size_t x, const std::size_t y, const std::size_t z) noexcept
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }
  };
}  // namespace mpbp

#endif
