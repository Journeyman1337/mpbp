#include <cmath>
#include <mpbp/Rect.hpp>

mpbp::Rect::Rect(std::size_t identifier, int width, int height) noexcept
    : identifier(identifier), width(width), height(height)
{
}

void mpbp::Rect::Place(int x, int y, int z) noexcept
{
  this->x = x;
  this->y = y;
  this->z = z;
}

int mpbp::Rect::GetX() const noexcept { return this->x; }

int mpbp::Rect::GetY() const noexcept { return this->y; }

int mpbp::Rect::GetZ() const noexcept { return this->z; }

int mpbp::Rect::GetFarX() const noexcept { return this->x + this->width - 1; }

int mpbp::Rect::GetFarY() const noexcept { return this->y + this->height - 1; }

int mpbp::Rect::GetWidth() const noexcept { return this->width; }

int mpbp::Rect::GetHeight() const noexcept { return this->height; }

std::size_t mpbp::Rect::GetIdentifier() const noexcept { return this->identifier; }

int mpbp::Rect::GetMaxDimension() const noexcept { return std::max(this->width, this->height); }

bool mpbp::Rect::GetIsDegenerate() const noexcept { return this->width <= 0 || this->height <= 0; }

std::strong_ordering mpbp::Rect::operator<=>(const mpbp::Rect& other) const noexcept
{
  return this->GetMaxDimension() <=> other.GetMaxDimension();
}