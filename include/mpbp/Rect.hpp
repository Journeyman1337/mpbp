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
  /**
   * @brief Bin packable axis-alligned rectangle.
   * 
   * This class is used to define the sizes of rectangles to pack. When packing is complete, the positions that the rectangles were packed can be retrieved from the getters of this class.
   */
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
    /**
     * @brief Construct a new Rect with default values.
     * 
     * A Rect created with this constructor will have a width and height of 0, meaning that it will cause exceptions if it is added to a pack. To set the width and height along with the identifier, the overloaded constructor should be used instead.
     */
    constexpr Rect() noexcept = default;
    /**
     * @brief Construct a new Rect object with a specific identifier, width, and height.
     * 
     * @param identifier A value used to differentiate this Rect from all other Rect in a pack span of Rect.
     * @param width The width of the Rect.
     * @param height The height of the Rect.
     */
    Rect(std::size_t identifier, int width, int height) noexcept;
    /**
     * @brief Place a Rect at the given position.
     * 
     * This function is used to place a Rect at a specific position within a set of bin pages. Before this function is called, the x, y and z values are all -1. This function is used within the packing algorithm, and is usually not useful for end user use.
     * 
     * @param x The x coordinate of the top left corner of the Rect.
     * @param y The y coordinate of the top left corner of the Rect.
     * @param z The bin page that the Rect exists on.
     */
    void Place(int x, int y, int z) noexcept;
    /**
     * @brief Get the x coordinate of the left side of the Rect.
     * 
     * @return The x coordinate of the left side of the Rect.
     */
    int GetX() const noexcept;
    /**
     * @brief Get the y coordinate of the top side of the Rect.
     * 
     * @return The y coordinate of the top side of the Rect.
     */
    int GetY() const noexcept;
    /**
     * @brief Get the bin page that the Rect exists on.
     * 
     * @return The index of the bin page this Rect eixts on.
     */
    int GetZ() const noexcept;
    /**
     * @brief Get the x coordinate of the right side of the Rect.
     * 
     * @return The x coordinate of the right side of the Rect.
     */
    int GetFarX() const noexcept;
    /**
     * @brief Get the y coordinate of the bottom side of the Rect.
     * 
     * @return The y coordinate of the bottom side of the Rect.
     */
    int GetFarY() const noexcept;
    /**
     * @brief Get the width of the Rect.
     * 
     * @return The width of the Rect.
     */
    int GetWidth() const noexcept;
    /**
     * @brief Get the height of the Rect.
     * 
     * @return The height of the Rect.
     */
    int GetHeight() const noexcept;
    /**
     * @brief Get the value used to idenitfy this Rect.
     * 
     * This value is used to differentiate this Rect from other Rect in its span during packing.
     * 
     * @return The identifier of this Rect.
     */
    std::size_t GetIdentifier() const noexcept;
    /**
     * @brief Get the size of the largest dimension of this Rect.
     * 
     * This is the maximum value between the width and the height of the Rect.
     * 
     * @return The size of the largest dimension.
     */
    int GetMaxDimension() const noexcept;
    /**
     * @brief Get if this Rect is degenerate.
     * 
     * A degenerate Rect has a width or height that is less than or equal to 0.
     * 
     * @return If the Rect is degenerate.
     */
    bool GetIsDegenerate() const noexcept;
    /**
     * @brief Compare this Rect with a different Rect.
     * 
     * This comparison compares the max dimensions of each Rect. It use used internally by the pack algorithm.
     * 
     * @return The strong ordering of the Rect.
     */
    std::strong_ordering operator<=>(const mpbp::Rect& other) const noexcept;
  };
}  // namespace mpbp

#endif