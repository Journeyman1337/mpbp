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

#include <mpbp/mpbp.hpp>
#include <iostream>

int main()
{
    std::vector<mpbp::input_rect> input_rects = 
    {
        mpbp::input_rect(0, 1, 1),
        mpbp::input_rect(1, 2, 2),
        mpbp::input_rect(2, 4, 4),
        mpbp::input_rect(3, 5, 7),
        mpbp::input_rect(4, 9, 10),
        mpbp::input_rect(5, 1, 1)
    };

    mpbp::Packer packer;
    packer.SetSize(32, 16);
    packer.Pack(input_rects);

    for (int y = 0; y < 16; y ++)
    {
        for (int x = 0; x < 32; x++)
        {
            bool rect_found = false;
            for (const auto& rect : input_rects)
            {
                if (rect.x <= x && rect.y <= y && rect.far_x() >= x && rect.far_y() >= y)
                {
                    std::cout << rect.identifier;
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


    return 0;
}
