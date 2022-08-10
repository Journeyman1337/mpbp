// SPDX-FileCopyrightText: 2022 Daniel Valcour <fossweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#include <cmath>
#include <mpbp/Rect.hpp>

mpbp::Rect::Rect(std::size_t identifier, int width, int height) noexcept
    : identifier(identifier), width(width), height(height)
{
}

void mpbp::Rect::Place(int left_x, int top_y, int page) noexcept
{
  this->left_x = left_x;
  this->top_y = top_y;
  this->page = page;
}

int mpbp::Rect::GetLeftX() const noexcept { return this->left_x; }

int mpbp::Rect::GetTopY() const noexcept { return this->top_y; }

int mpbp::Rect::GetPage() const noexcept { return this->page; }

int mpbp::Rect::GetRightX() const noexcept { return this->left_x + this->width - 1; }

int mpbp::Rect::GetBottomY() const noexcept { return this->top_y + this->height - 1; }

int mpbp::Rect::GetWidth() const noexcept { return this->width; }

int mpbp::Rect::GetHeight() const noexcept { return this->height; }

std::size_t mpbp::Rect::GetIdentifier() const noexcept { return this->identifier; }

int mpbp::Rect::GetMaxDimension() const noexcept { return std::max(this->width, this->height); }

bool mpbp::Rect::GetIsDegenerate() const noexcept { return this->width <= 0 || this->height <= 0; }

std::strong_ordering mpbp::Rect::operator<=>(const mpbp::Rect& other) const noexcept
{
  return this->GetMaxDimension() <=> other.GetMaxDimension();
}