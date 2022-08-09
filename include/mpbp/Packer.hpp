// SPDX-FileCopyrightText: 2022 Daniel Valcour <fossweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

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
