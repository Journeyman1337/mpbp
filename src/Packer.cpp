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

#include <algorithm>
#include <mpbp/Packer.hpp>
#include <stdexcept>

mpbp::Packer::Packer(std::size_t max_width, std::size_t max_height) noexcept
  : max_width(max_width), max_height(max_height)
{}

void mpbp::Packer::Clear() noexcept
{
  this->spaces.clear();
  this->page_count = 0;
  this->width = 0;
  this->height = 0;
  this->top_bin_width = 0;
  this->top_bin_height = 0;
}

void mpbp::Packer::SetSize(std::size_t max_width, std::size_t max_height)
{
  this->Clear();
  this->max_width = max_width;
  this->max_height = max_height;
}

const std::vector<mpbp::Space>& mpbp::Packer::GetSpaces() const noexcept { return this->spaces; }

std::size_t mpbp::Packer::GetPageCount() const noexcept { return this->page_count; }

std::size_t mpbp::Packer::GetWidth() const noexcept { return this->width; }

std::size_t mpbp::Packer::GetHeight() const noexcept { return this->height; }

std::size_t mpbp::Packer::GetMaxWidth() const noexcept { return this->max_width; }

std::size_t mpbp::Packer::GetMaxHeight() const noexcept { return this->max_height; }

std::size_t mpbp::Packer::GetTopBinWidth() const noexcept { return this->top_bin_width; }

std::size_t mpbp::Packer::GetTopBinHeight() const noexcept { return this->top_bin_height; }

void mpbp::Packer::reserveSpaces(const std::span<mpbp::Rect>& rects)
{
  const auto highest_new_space_count = rects.size() * 2;
  const auto new_space_capacity = this->spaces.size() + highest_new_space_count;
  this->spaces.reserve(new_space_capacity);
}

bool mpbp::Packer::tryPlaceSpace(mpbp::Rect& rect)
{
  for (std::size_t space_i = 0; space_i < this->spaces.size(); space_i++)
  {
    auto& space = this->spaces[space_i];
    if (space.Fits(rect))
    {
      rect.Place(space.GetX(), space.GetY(), space.GetZ());
      // If the extra space to the right of the rect is greater than the extra space bellow...
      if (space.GetWidth() - rect.GetWidth() > space.GetHeight() - rect.GetHeight())
      {
        // If there is leftover space to the right of the rect within the containing space...
        if (rect.GetWidth() < space.GetWidth())
        {
          // Place a space to the right that reaches down to the bottom of the rect.
          this->spaces.emplace_back(rect.GetFarX() + 1, rect.GetY(), space.GetZ(),
                                    space.GetWidth() - rect.GetWidth(), rect.GetHeight());
        }
        // If there is leftover space bellow the rect within the containing space...
        if (rect.GetHeight() < space.GetHeight())
        {
          // Place a space bellow that reaches to the right of the containing space.
          this->spaces.emplace_back(rect.GetX(), rect.GetFarY() + 1, space.GetZ(), space.GetWidth(),
                                    space.GetHeight() - rect.GetHeight());
        }
      }
      // If the space above and bellow are the same size, or the bottom gap is bigger than the
      // right gap.
      else  // if (cur_space.width - cur_rect->width <= cur_space.height - cur_rect->height)
      {
        // If there is leftover space to the right of the rect within the containing space...
        if (rect.GetWidth() < space.GetWidth())
        {
          // Place a space to the right of the rect that reaches down to the bottom of the
          // containing space.
          this->spaces.emplace_back(rect.GetX(), rect.GetFarY() + 1, space.GetZ(), space.GetWidth(),
                                    space.GetHeight() - rect.GetHeight());
        }
        // If there is leftover space bellow the rect within the containing space...
        if (rect.GetHeight() < space.GetHeight())
        {
          // Place a space bellow the rect that reaches only to the width of the rect.
          this->spaces.emplace_back(rect.GetX(), rect.GetFarY() + 1, space.GetZ(), rect.GetWidth(),
                                    space.GetHeight() - rect.GetHeight());
        }
      }
      this->spaces[space_i] = this->spaces[this->spaces.size() - 1];
      this->spaces.pop_back();
      std::sort(this->spaces.begin(), this->spaces.end());
      return true;
    }
  }
  return false;
}

bool mpbp::Packer::tryPlaceExpandBin(mpbp::Rect& rect)
{
  auto place_rect_right = [&]()
  {
    rect.Place(this->top_bin_width, 0, this->getTopPageI());
    this->top_bin_width += rect.GetWidth();
    if (rect.GetHeight() <= this->top_bin_height)
    {
      spaces.emplace_back(rect.GetX(), rect.GetHeight(), this->getTopPageI(), rect.GetWidth(),
                          this->top_bin_height - rect.GetHeight());
    }
    if (this->page_count == 1)
    {
      this->width = this->top_bin_width;
    }
  };
  auto place_rect_bellow = [&]()
  {
    rect.Place(0, this->top_bin_height, this->getTopPageI());
    this->top_bin_height += rect.GetHeight();
    if (rect.GetWidth() <= this->top_bin_width)
    {
      spaces.emplace_back(rect.GetWidth(), rect.GetY(), this->getTopPageI(),
                          this->top_bin_width - rect.GetWidth(), rect.GetHeight());
    }
    if (this->page_count == 1)
    {
      this->height = this->top_bin_height;
    }
  };
  const auto fits_bellow = this->top_bin_height + rect.GetHeight() <= this->max_height;
  const auto fits_right = this->top_bin_width + rect.GetWidth() <= this->max_width;
  /*
      Weight the placement choice based on the placed bin has a larger width or height.
  */
  if (fits_bellow && this->top_bin_height <= this->top_bin_width)
  {
    place_rect_bellow();
    return true;
  }
  else if (fits_right && this->top_bin_width <= this->top_bin_height)
  {
    place_rect_right();
    return true;
  }
  /*
      If the weigted conditions don't pass, try them again without the weights.
  */
  else if (fits_bellow)
  {
    place_rect_bellow();
    return true;
  }
  else if (fits_right)
  {
    place_rect_right();
    return true;
  }
  return false;
}

void mpbp::Packer::spaceLeftoverPage()
{
  if (this->top_bin_width < this->max_height)
  {
    this->spaces.emplace_back(this->top_bin_width, 0, this->max_width - this->top_bin_width,
                              this->top_bin_height, this->getTopPageI());
  }
  if (this->top_bin_height < this->max_height)
  {
    this->spaces.emplace_back(0, this->top_bin_height, this->top_bin_width,
                              this->max_height - this->top_bin_height, this->getTopPageI());
  }
}

void mpbp::Packer::placeNewPage(mpbp::Rect& rect)
{
  this->page_count++;
  rect.Place(0, 0, this->getTopPageI());
  if (this->page_count == 1)
  {
    this->width = rect.GetWidth();
    this->height = rect.GetHeight();
  }
  this->top_bin_width = rect.GetWidth();
  this->top_bin_height = rect.GetHeight();
}

std::size_t mpbp::Packer::getTopPageI() const noexcept { return this->page_count - 1; }

void mpbp::Packer::Pack(const std::span<mpbp::Rect> rects)
{
  if (rects.size() == 0) return;
  if (this->max_width == 0 || this->max_height == 0)
  {
    throw std::runtime_error("invalid max page dimensions");
  }
  for (const auto& rect : rects)
  {
    if (rect.GetIsDegenerate())
    {
      throw std::runtime_error("one or more rects are degenerate");
    }
  }
  std::sort(rects.begin(), rects.end(), std::greater());
  std::size_t rect_i = 0;
  auto rect = &rects[rect_i++];
  if (rect->GetWidth() > this->max_width || rect->GetHeight() > this->max_height)
  {
    throw std::runtime_error("one or more rects do not fit in bin");
  }
  this->reserveSpaces(rects);
  auto top_page_i = [&]() -> std::size_t { return this->page_count - 1; };
  auto next_rect = [&]() { rect = &rects[++rect_i]; };
  if (this->page_count == 0)
  {
    this->placeNewPage(*rect);
    next_rect();
  }
  for (; rect_i < rects.size(); next_rect())
  {
    if (this->tryPlaceSpace(*rect)) continue;
    if (this->tryPlaceExpandBin(*rect)) continue;
    this->spaceLeftoverPage();
    this->placeNewPage(*rect);
  }
  this->spaces.shrink_to_fit();
}
