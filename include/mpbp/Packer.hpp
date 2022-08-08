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

#ifndef MPBP_PACKER_HPP
#define MPBP_PACKER_HPP

#include <mpbp/Rect.hpp>
#include <mpbp/Space.hpp>
#include <span>
#include <vector>

namespace mpbp
{
  class Packer
  {
   private:
    std::vector<mpbp::Space> spaces = std::vector<mpbp::Space>();
    int page_count = 0;
    int width = 0;
    int height = 0;
    int max_width = 0;
    int max_height = 0;
    int top_bin_width = 0;
    int top_bin_height = 0;

    void reserveSpaces(const std::span<mpbp::Rect>& rects);
    bool tryPlaceSpace(mpbp::Rect& rect);
    bool tryPlaceExpandBin(mpbp::Rect& rect);
    void spaceLeftoverPage();
    void placeNewPage(mpbp::Rect& rect);
    int getTopPageI() const noexcept;

   public:
    constexpr Packer() noexcept = default;
    Packer(int max_width, int max_height) noexcept;

    void Clear() noexcept;
    void SetMaxPageSize(int max_width, int max_height);
    const std::vector<mpbp::Space>& GetSpaces() const noexcept;
    int GetPageCount() const noexcept;
    int GetWidth() const noexcept;
    int GetHeight() const noexcept;
    int GetMaxWidth() const noexcept;
    int GetMaxHeight() const noexcept;
    int GetTopBinWidth() const noexcept;
    int GetTopBinHeight() const noexcept;
    void Pack(const std::span<mpbp::Rect> rects);
  };
}  // namespace mpbp

#endif
