<!--
SPDX-FileCopyrightText: 2022 Daniel Valcour <fossweeper@gmail.com>

SPDX-License-Identifier: MIT
-->

# Multi Page Bin Packing Library

[![Tests](https://github.com/Journeyman-dev/mpbp/actions/workflows/Test.yaml/badge.svg)](https://github.com/Journeyman-dev/mpbp/actions/workflows/Test.yaml)

**NOTE: This library is a work in progress.**

mpbp is a bin packing library with support for a dynamic number of bins using a First-Fit packing algorithm. The library targets C++ 20, and is heavily documented and unit tested. The algorithm itself is explained in detail through the use of code comments. It is not the fastest or the most space efficient algorithm that is known, but it gets the job done. It is possible to use this library for both online and offline bin packing. When using it for offline packing, the the algorithm will qualify as First-Fit-Decreasing, meaning that it is much more space efficient.
