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
#include <mpbp/input_rect.hpp>
#include <mpbp/pack_rect.hpp>
#include <stdexcept>

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

const std::vector<mpbp::pack_rect>& mpbp::Packer::GetSpaces() const noexcept
{
  return this->spaces;
}

std::size_t mpbp::Packer::GetPageCount() const noexcept { return this->page_count; }

std::size_t mpbp::Packer::GetWidth() const noexcept { return this->width; }

std::size_t mpbp::Packer::GetHeight() const noexcept { return this->height; }

std::size_t mpbp::Packer::GetMaxWidth() const noexcept { return this->max_width; }

std::size_t mpbp::Packer::GetMaxHeight() const noexcept { return this->max_height; }

std::size_t mpbp::Packer::GetTopBinWidth() const noexcept { return this->top_bin_width; }

std::size_t mpbp::Packer::GetTopBinHeight() const noexcept { return this->top_bin_height; }

void mpbp::Packer::Pack(const std::span<mpbp::input_rect> input_rects)
{
  /*
      First, we need to make sure that the rect pack can occur without issues.
  */
  // Return if there is nothing to pack.
  if (input_rects.size() == 0) return;
  // Make sure the max page dimensions are nonzero.
  if (this->max_width == 0 || this->max_height == 0)
  {
    throw std::runtime_error("invalid max page dimensions");
  }
  // Sort the input rects, largest to smallest.
  std::sort(input_rects.begin(), input_rects.end());
  // Retrieve the smallest input rect.
  auto cur_rect_i = 0;
  auto cur_rect = &input_rects[cur_rect_i];
  // Determine if it has a 0 dimension.
  if (cur_rect->is_degenerate())
  {
    throw std::runtime_error("one or more input rects are degenerate");
  }
  // Retrieve the largest input rect.
  cur_rect_i = input_rects.size() - 1;
  cur_rect = &input_rects[cur_rect_i];
  // Determine if the largest rect is too large for the max bin dimensions.
  if (cur_rect->width > this->max_width || cur_rect->height > this->max_height)
  {
    throw std::runtime_error("one or more input rects do not fit in bin");
  }
  /*
      After this point, we know that packing can occur without issues.
      Now we can edit the class parameters and perform the pack.
  */
  // Reserve more memory in the spaces vector to lower allocation count of this algorithm.
  {
    // The largest amount of new spaces possible is twice the amount of input rects.
    const auto highest_new_space_count = input_rects.size() * 2;
    // Add this amount to the amount of spaces that already exist in the spaces vector.
    const auto new_space_capacity = this->spaces.size() + highest_new_space_count;
    // Expand the memory of the spaces vector by that capactiy.
    this->spaces.reserve(new_space_capacity);
  }
  // Define some utility lambdas.
  auto top_page_i = [&]() -> std::size_t { return this->page_count - 1; };
  auto next_rect = [&]() { cur_rect = &input_rects[--cur_rect_i]; };
/*
    Now, it is time to start placing...
*/
/*
    The first rect is always placed the same way.
*/
// If no rects have been placed yet (including in any previous packs in case this is offline)...
if (this->page_count == 0)
{
  // Start creating the first page.
  this->page_count = 1;
  // Place the current rect at the top left corner of the first page.
  cur_rect->place(0, 0, 0);
  this->width = cur_rect->width;
  this->height = cur_rect->height;
  // Expand the top page to match the size of the current rect.
  this->top_bin_width = cur_rect->width;
  this->top_bin_height = cur_rect->height;
  // Decrement to the next smallest rect.
  next_rect();
}
// Create goto label to easily iterate to the next rect in the loop.
PACK_LOOP_START:  // goto is normally frowned upon, except sometimes in situations like these...
  // Loop through all remaining input rects, largest to smallest.
  while (cur_rect_i != 0)
  {
    // Decrement to the next smallest rect.
    next_rect();
    /*
        After the first rect, the first placement oportunity to test for is for the smallest empty
       space that the rect fits in.
    */
    // Loop through all spaces, smallest to largest.
    for (std::size_t space_i = 0; space_i < spaces.size(); space_i++)
    {
      // Get the current space at space_i.
      auto& cur_space = this->spaces[space_i];
      // If the rect fits this space, we found a place to put it.
      if (cur_space.fits(*cur_rect))
      {
        // Place the rect inside of the space.
        cur_rect->place(cur_space.x, cur_space.y, cur_space.z);
        /*
            If any remaining space is left over in the current space outside the rect, we should
           divide that area up into new spaces. To optimize placement, should try to place these
           spaces to keep them as square as possible.
         */
        // If the extra space to the right of the rect is greater than the extra space bellow...
        if (cur_space.width - cur_rect->width > cur_space.height - cur_rect->height)
        {
          // If there is leftover space to the right of the rect within the containing space...
          if (cur_rect->width < cur_space.width)
          {
            // Place a space to the right that reaches down to the bottom of the rect.
            this->spaces.emplace_back(cur_rect->far_x() + 1, cur_rect->y, cur_space.z,
                                      cur_space.width - cur_rect->width, cur_rect->height);
          }
          // If there is leftover space bellow the rect within the containing space...
          if (cur_rect->height < cur_space.height)
          {
            // Place a space bellow that reaches to the right of the containing space.
            this->spaces.emplace_back(cur_rect->x, cur_rect->far_y() + 1, cur_space.z, cur_space.width,
                                      cur_space.height - cur_rect->height);
          }
        }
        // If the space above and bellow are the same size, or the bottom gap is bigger than the
        // right gap.
        else  // if (cur_space.width - cur_rect->width <= cur_space.height - cur_rect->height)
        {
          // If there is leftover space to the right of the rect within the containing space...
          if (cur_rect->width < cur_space.width)
          {
            // Place a space to the right of the rect that reaches down to the bottom of the
            // containing space.
            this->spaces.emplace_back(cur_rect->x, cur_rect->far_y() + 1, cur_space.z, cur_space.width,
                                      cur_space.height - cur_rect->height);
          }
          // If there is leftover space bellow the rect within the containing space...
          if (cur_rect->height < cur_space.height)
          {
            // Place a space bellow the rect that reaches only to the width of the rect.
            this->spaces.emplace_back(cur_rect->x, cur_rect->far_y() + 1, cur_space.z, cur_rect->width,
                                      cur_space.height - cur_rect->height);
          }
        }
        /*
            We now need to remove the containing space, because it is entirely filled in with the
           rect and new spaces.
        */
        // Overwrite the containing space with the last space in the spaces vector.
        this->spaces[space_i] = this->spaces[this->spaces.size() - 1];
        // Remove the last space from the spaces vector.
        this->spaces.pop_back();
        // Sort the spaces vector from smallest to largest.
        std::sort(this->spaces.begin(), this->spaces.end());
        // Restart the input rect placement loop to place the next input rect.
        goto PACK_LOOP_START;
      }
    }
    /*
        If there were no empty spaces available that the rect fits in, we need to try to expand the
       top page bin size and place the rect bellow or to the right of all rects placed on the
       current page. To optimize rect placement, it is best to do the placement in a way to keep the
       total bin as square as possible.
    */
    {
      // Define a lambda to place the rect to the right of the top page bin.
      auto place_rect_right = [&]()
      {
        cur_rect->place(this->top_bin_width, 0, top_page_i());
        this->top_bin_width += cur_rect->width;
        if (cur_rect->height <= this->top_bin_height)
        {
          spaces.emplace_back(cur_rect->x, cur_rect->height, top_page_i(), cur_rect->width,
                              this->top_bin_height - cur_rect->height);
        }
        if (this->page_count == 1)
        {
          this->width = this->top_bin_width;
        }
      };
      // Define a lambda to place the rect to the bottom of the top page bin.
      auto place_rect_bellow = [&]()
      {
        cur_rect->place(0, this->top_bin_height, top_page_i());
        this->top_bin_height += cur_rect->height;
        if (cur_rect->width <= this->top_bin_width)
        {
          spaces.emplace_back(cur_rect->width, cur_rect->y, top_page_i(),
                              this->top_bin_width - cur_rect->width, cur_rect->height);
        }
        if (this->page_count == 1)
        {
          this->height = this->top_bin_height;
        }
      };
      // Determine if the rect fits above or bellow the packed bin on the top page.
      const auto fits_bellow = this->top_bin_height + cur_rect->height <= this->max_height;
      const auto fits_right = this->top_bin_width + cur_rect->width <= this->max_width;
      /*
          Weight the placement choice based on the placed bin has a larger width or height.
      */
      if (fits_bellow && this->top_bin_height <= this->top_bin_width)
      {
        // Place the rect bellow the bin.
        place_rect_bellow();
        // Restart the input rect placement loop to place the next input rect.
        goto PACK_LOOP_START;
      }
      else if (fits_right && this->top_bin_width <= this->top_bin_height)
      {
        // Place the rect to the right of the bin.
        place_rect_right();
        // Restart the input rect placement loop to place the next input rect.
        goto PACK_LOOP_START;
      }
      /*
          If the weigted conditions don't pass, try them again without the weights.
      */
      else if (fits_bellow)
      {
        // Place the rect bellow the bin.
        place_rect_bellow();
        // Restart the input rect placement loop to place the next input rect.
        goto PACK_LOOP_START;
      }
      else if (fits_right)
      {
        // Place the rect to the right of the bin.
        place_rect_right();
        // Restart the input rect placement loop to place the next input rect.
        goto PACK_LOOP_START;
      }
    }
    /*
        If there are no other placement options available, the only thing left that can be done is
       to add a new page and place the rect on the top left corner. First though, any remaining
       space on the current page should be stored in the spaces vector.
     */
    // If there is remaining space to the right...
    if (this->top_bin_width < this->max_height)
    {
      // Add a space for the remaining space to the right going all the way to the bottom of the
      // page.
      this->spaces.emplace_back(this->top_bin_width, 0, this->max_width - this->top_bin_width,
                                this->top_bin_height, top_page_i());
    }
    // If there is remaining space bellow...
    if (this->top_bin_height < this->max_height)
    {
      // Add a space for the remaining space bellow reaching only to the width of the bin.
      this->spaces.emplace_back(0, this->top_bin_height, this->top_bin_width,
                                  this->max_height - this->top_bin_height, top_page_i());
    }
    // After the first page is done, the width and height of all pages is now the max.
    this->width = this->max_width;
    this->height = this->max_height;
    // Increment the page count.
    this->page_count++;
    // Place the rect at the top left corner of the new page.
    cur_rect->place(0, 0, top_page_i());
    // Make the top page bin dimensions match the rect.
    this->top_bin_width = cur_rect->width;
    // Restart the input rect placement loop to place the next input rect.
    goto PACK_LOOP_START;
  }
}
