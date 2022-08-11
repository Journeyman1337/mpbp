<!--
SPDX-FileCopyrightText: 2022 Daniel Valcour <fossweeper@gmail.com>

SPDX-License-Identifier: MIT
-->

# Multi Page Bin Packing Library

[![Tests](https://github.com/Journeyman-dev/mpbp/actions/workflows/Test.yaml/badge.svg)](https://github.com/Journeyman-dev/mpbp/actions/workflows/Test.yaml)

This site contains the documentation for the mpbp library. mpbp (<b>M</b>ulti-<b>P</b>age <b>B</b>in <b>P</b>acking library) is a free and open source library for bin packing written in C++ 20. It provides an easy to use bin packing algorithm with support for both offline and online packing. mpbp tries to optimally place Rects in multiple bins of a specific size in as few bins as possible. This system is designed for usage in creating sprite batch rendering systems that utilize more than one texture atlas page.