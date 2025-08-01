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
#include "../include/controllers/NetworkScanningControllers.hpp"
#include "../include/controllers/PingControllers.hpp"
#include "../include/tools/drawAppIcon.hpp"
#include "include/controllers/NetworkScanningControllers.hpp"

#include <iostream>

enum class MenuOption {
   PING     = 1,
   SCANNING = 2,
   EXIT     = 3,
};

int main(int argc, char* argv[])
{
   PingControllers pingControllers;
   NetworkScanningControllers networkScanningControllers;

   while (true) {
      std::cout << "\033[2J\033[H";
      drawAppIcon();
      int selectedOption {0};
      std::cout << "Welcome to MooPing\n";
      std::cout << "MooPing menu\n";
      std::cout << "(1) Pinging Mode\n";
      std::cout << "(2) Network Scanning Mode\n";
      std::cout << "(3) Exit\n";
      std::cin >> selectedOption;
      switch (static_cast<MenuOption>(selectedOption)) {
         case MenuOption::PING:
            pingControllers.startPingingMode();
            break;
         case MenuOption::SCANNING:
            networkScanningControllers.startScanningMode();
            break;
         case MenuOption::EXIT:
            return 0;
            break;
      }
   }
}