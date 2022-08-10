// SPDX-FileCopyrightText: 2022 Daniel Valcour <fossweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#include <iostream>
#include <mpbp/mpbp.hpp>

int main()
{
  std::vector<mpbp::Rect> input_rects = {
      mpbp::Rect(0, 1, 1), mpbp::Rect(1, 2, 2),  mpbp::Rect(2, 4, 4), mpbp::Rect(3, 5, 5),
      mpbp::Rect(4, 7, 7), mpbp::Rect(5, 7, 7),  mpbp::Rect(6, 6, 6), mpbp::Rect(7, 9, 9),
      mpbp::Rect(8, 6, 6), mpbp::Rect(9, 30, 15)};

  mpbp::Packer packer(32, 16);
  packer.Pack(input_rects);

  for (int page = 0; page < packer.GetPageCount(); page++)
  {
    std::cout << "page " << page << std::endl;
    for (int y = 0; y < 16; y++)
    {
      for (int x = 0; x < 32; x++)
      {
        bool rect_found = false;
        for (const auto& rect : input_rects)
        {
          if (rect.GetPage() == page && rect.GetLeftX() <= x && rect.GetTopY() <= y && rect.GetRightX() >= x &&
              rect.GetBottomY() >= y)
          {
            std::cout << rect.GetIdentifier();
            rect_found = true;
            break;
          }
        }
        if (!rect_found)
        {
          std::cout << ".";
        }
      }
      std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
  }

  /*
    page 0
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    999999999999999999999999999999..
    ................................


    page 1
    7777777775555555888888..........
    7777777775555555888888..........
    7777777775555555888888..........
    7777777775555555888888..........
    7777777775555555888888..........
    7777777775555555888888..........
    777777777555555533333...........
    777777777666666.33333...........
    777777777666666.33333...........
    4444444..666666.33333...........
    4444444..666666.33333...........
    4444444..666666.2222............
    4444444..666666.2222............
    4444444..11.....2222............
    4444444..11.....2222............
    4444444.........0...............
  */

  return 0;
}
