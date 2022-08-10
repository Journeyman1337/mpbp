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
  /**
   * @brief Bin packing algorithm runner and state machine.
   * 
   * This class stores all state data used for bin packing, and is used to perform bin packs.
   */
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
    /**
     * @brief Construct a new Packer object with default values.
     * 
     * This will construct a Packer object with default values. If the Packer is constructed using this, need to specify the maximum page size using Packer::SetMaxPageSize() before you can pack.
     */
    constexpr Packer() noexcept = default;
    /**
     * @brief Construct a new Packer object with a specified maximum bin size.
     * 
     * This constructor allows creating a Packer object and setting its maximum page size in one statement.
     * 
     * @param max_width The maximum width of a bin page.
     * @param max_height The maximum height of a bin page.
     */
    Packer(int max_width, int max_height) noexcept;
    /**
     * @brief Clear the Packer of data from all previous packs.
     * 
     */
    void Clear() noexcept;
    /**
     * @brief Set the Max Page Size objectChange the maximum bin size and clear the Packer state data.
     * 
     * @param max_width The maximum width of a bin page.
     * @param max_height The maximum height of a bin page.
     */
    void SetMaxPageSize(int max_width, int max_height);
    /**
     * @brief Get the vector of all Space  between Rect from all previous packs.
     * 
     * @return An immutable reference to the Space vector.
     */
    const std::vector<mpbp::Space>& GetSpaces() const noexcept;
    /**
     * @brief Get the amount of bin pages from all previous packs.
     * 
     * @return The amount of pages.
     */
    int GetPageCount() const noexcept;
    /**
     * @brief Get the width of all bin pages. 
     * 
     * If all Rect have been packed in less than a single bin page, this width will be smaller than the maximum width. Otherwise, it will be equal to the maximum width.
     * 
     * @return The width of all bin pages. 
     */
    int GetWidth() const noexcept;
    /**
     * @brief Get the height of all bin pages. 
     * 
     * If all Rect have been packed in less than a single bin page, this height will be smaller than the maximum height. Otherwise, it will be equal to the maximum height.
     * 
     * @return The height of all bin pages. 
     */
    int GetHeight() const noexcept;
    /**
     * @brief Get the maximum width of bin pages.
     * 
     * @return The maximum width of bin pages.
     */
    int GetMaxWidth() const noexcept;
    /**
     * @brief Get the maximum height of bin pages.
     * 
     * @return The maximum height of bin pages.
     */
    int GetMaxHeight() const noexcept;
    /**
     * @brief Get the width of the bounding rectangle of all Rect on the top page.
     * 
     * @return The width of the bounding rectangle of all Rect on the top page.
     */
    int GetTopBinWidth() const noexcept;
    /**
     * @brief Get the height of the bounding rectangle of all Rect on the top page.
     * 
     * @return The height of the bounding rectangle of all Rect on the top page.
     */
    int GetTopBinHeight() const noexcept;
    /**
     * @brief Run the pack algorithm with the given span of Rect.
     * 
     * @param The span of Rect to pack. 
     */
    void Pack(const std::span<mpbp::Rect> rects);
  };
}  // namespace mpbp

#endif
