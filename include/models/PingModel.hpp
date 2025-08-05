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

#include <boost/asio.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <memory>
#include <vector>

#include "../types/ICMPStructs.hpp"

/// @brief This model is responsible for ping host and receive ping response
/// @ingroup Models
class PingModel {
   using ICMPPackagesDataType = std::shared_ptr<ICMPPackageData>;

   public:
   PingModel();
   /// @brief This method send ping to destination IP
   void sendPing(std::string destination_ip);
   /// @brief This method receives the ping response and collects the ping packet data
   /// @return Returns a struct with ping package data
   [[nodiscard]] ICMPPackagesDataType receivePing();

   private:
   std::vector<uint8_t> constructICMPPackage(const std::string body);

   int packageSequenceNumber {1};
   boost::asio::io_context _context;
   boost::asio::ip::icmp::socket _socket;
   const std::string _packageBody {"Ping from MooPing"};
   std::string destinationAddress {};

   std::chrono::steady_clock::time_point _startTime;
};