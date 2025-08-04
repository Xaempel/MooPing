/*******************************************************************************
**                                                                            **
**  Copyright (C) [2025] [Xaempel]                                            **
**                                                                            **
**  This file is part of [MooPing].                                           **
**  [MooPing] is free software: you can redistribute it and/or                **
**  modify it under the terms of the GNU General Public License as published  **
**  by the Free Software Foundation, either version 2 of the License, or any  **
**  later version.                                                            **
**                                                                            **
**  [MooPing] is distributed in the hope that it will be                      **
**  useful, but WITHOUT ANY WARRANTY; without even the implied warranty of    **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             **
**  GNU General Public License for more details.                              **
**                                                                            **
**  You should have received a copy of the GNU General Public License along   **
**  with [MooPing].  If not, see <https://www.gnu.org/licenses/>.             **
**                                                                            **
*******************************************************************************/
#pragma once

#include <cstdint>
#include <string>

struct ICMPPackageData {
   uint32_t size {0};
   int sequenceNumber {0};
   int ttl {0};
   double time {0.0};
   std::string destinationAddress {};
};

struct ICMPHeader {
   std::uint8_t type {8};
   std::uint8_t code {0};
   std::uint16_t checksum {0};
   std::uint16_t identifier {0};
   std::uint16_t sequenceNumber {0};
};
