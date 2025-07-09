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
#include <vector>
#include <memory>
#include <string>

struct ICMPPackageData {
   uint32_t size = 0;
   int sequenceNumber = 0;
};

class PingModel {
   using ICMPPackagesDataListType = std::shared_ptr<ICMPPackageData>;

   public:
   void sendPing(std::string destination_ip);
   void showPackageInfo(int idOfPackage);

   private:
   int packageSequenceNumber {1};
   std::vector<ICMPPackagesDataListType> ICMPPackagesData {};
};