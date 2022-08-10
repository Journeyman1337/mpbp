// SPDX-FileCopyrightText: 2022 Daniel Valcour <fossweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef MPBP_SPACE_HPP
#define MPBP_SPACE_HPP

#include <compare>

namespace mpbp
{
  /**
   * @brief An axis-alligned rectangular space between packed Rect in a set of bin pages.
   * 
   * This class is used internally by the pack algorithm to keep track of spaces between Rect. It has little use to end users in most situations.
   * 
   */
  struct Rect;

  class Space
  {
   private:
    int max_dimension = 0;
    int left_x = 0;
    int top_y = 0;
    int page = 0;
    int width = 0;
    int height = 0;

   public:
    /**
     * @brief Construct a new Space with default values.
     * 
     * The position coordinates, page, width, and height are all set to 0.
     */
    constexpr Space() noexcept = default;
    /**
     * @brief Construct a new Space object at the given coordinates and page with the given width and height.
     * 
     * @param left_x The x coordinate position of the top left corner of the Space.
     * @param top_y The y coordinate position of the top left corner of the Space.
     * @param page The bin page that this Space exists on.
     * @param width The width of the Space.
     * @param height The height of the Space.
     */
    Space(int left_x, int top_y, int page, int width, int height) noexcept;
    /**
     * @brief Get the x coordinate of the left side of the Space.
     * 
     * @return The x coordinate of the left side of the Space.
     */
    int GetLeftX() const noexcept;
    /**
     * @brief Get the y coordinate of the top side of the Space.
     * 
     * @return The y coordinate of the top side of the Space.
     */
    int GetTopY() const noexcept;
    /**
     * @brief Get the bin page that the Space exists on.
     * 
     * @return The index of the bin page this Space exists on.
     */
    int GetPage() const noexcept;
    /**
     * @brief Get the width of the Space.
     * 
     * @return The width of the Space.
     */
    int GetWidth() const noexcept;
    /**
     * @brief Get the height of the Space.
     * 
     * @return The height of the Space.
     */
    int GetHeight() const noexcept;
    /**
     * @brief Get the size of the largest dimension of this Space.
     * 
     * This is the maximum value between the width and the height of the Space.
     * 
     * @return The size of the largest dimension.
     */
    int GetMaxDimension() const noexcept;
    /**
     * @brief Get if this Space is degenerate.
     * 
     * A degenerate ReSpacect has a width or height that is less than or equal to 0.
     * 
     * @return If the Space is degenerate.
     */
    bool GetIsDegenerate() const noexcept;
    /**
     * @brief Compare this Space with a different Space.
     * 
     * This comparison compares the max dimensions of each Space. It use used internally by the pack algorithm.
     * 
     * @return The strong ordering of the Space.
     */
    std::strong_ordering operator<=>(const mpbp::Space& other) const noexcept;
    /**
     * @brief Get if a Space fits within the Rect.
     * 
     * @param The Rect to test fitting into the Space. 
     * 
     * @return If the Rect fits within the Space. 
     */
    bool Fits(const mpbp::Rect& rect) const noexcept;
  };
}  // namespace mpbp

#endif