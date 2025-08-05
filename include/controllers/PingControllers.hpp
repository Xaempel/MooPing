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

#include "AutomaticPingController.hpp"

/// @brief Class responsible for ping functions in app
/// @ingroup Controllers
class PingControllers {
   public:
   PingControllers();
   /// @brief Starts ping functions in app. This function is a entry point for ping functions in app, in future I'll add Single Ping Controller for single ping mode for now logic for this function is in it.
   void startPingingMode();

   private:
   bool isAdditionalInfoAboutPackages {false};
   PingModel pingModel {};
   AutomaticPingController automaticPingController;
};