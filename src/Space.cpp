// SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#include <cmath>
#include <mpbp/Rect.hpp>
#include <mpbp/Space.hpp>

mpbp::Space::Space(int left_x, int top_y, int page, int width, int height) noexcept
    : left_x(left_x), top_y(top_y), page(page), width(width), height(height), max_dimension(std::max(width, height))
{
}

int mpbp::Space::GetLeftX() const noexcept { return this->left_x; }

int mpbp::Space::GetTopY() const noexcept { return this->top_y; }

int mpbp::Space::GetPage() const noexcept { return this->page; }

int mpbp::Space::GetWidth() const noexcept { return this->width; }

int mpbp::Space::GetHeight() const noexcept { return this->height; }

int mpbp::Space::GetMaxDimension() const noexcept { return this->max_dimension; }

bool mpbp::Space::GetIsDegenerate() const noexcept { return this->width <= 0 || this->height <= 0; }

std::strong_ordering mpbp::Space::operator<=>(const mpbp::Space& other) const noexcept
{
  return this->max_dimension <=> other.max_dimension;
}

bool mpbp::Space::Fits(const mpbp::Rect& rect) const noexcept
{
  return this->width >= rect.GetWidth() && this->height >= rect.GetHeight();
}