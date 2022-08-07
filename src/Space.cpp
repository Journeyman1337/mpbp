#include <cmath>
#include <mpbp/Rect.hpp>
#include <mpbp/Space.hpp>

mpbp::Space::Space(int x, int y, int z, int width, int height) noexcept
    : x(x), y(y), z(z), width(width), height(height), max_dimension(std::max(x, y))
{
}

int mpbp::Space::GetX() const noexcept { return this->x; }

int mpbp::Space::GetY() const noexcept { return this->y; }

int mpbp::Space::GetZ() const noexcept { return this->z; }

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