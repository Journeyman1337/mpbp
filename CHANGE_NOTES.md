<!--
SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>

SPDX-License-Identifier: MIT
-->

# 1.0.2

## Bugfixes:
* Fixed degenerate Spaces sometimes being added to the Packer's space vector due to invalid constructor argument order.
* Fixed the last Rect of a pack being ignored.

## Tooling:
* Added new automatic tests to detect similar bugs to those patched in both this and the previous patch.

# 1.0.1

## Bugfixes:
* Fixed issue with Spaces being added to the Packer's space vector with a width or height of 0.

# 1.0

Initial release.
