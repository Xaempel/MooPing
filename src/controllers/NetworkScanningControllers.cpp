#include "../include/controllers/NetworkScanningControllers.hpp"

#include "../include/models/NetworkScanningModel.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

void NetworkScanningControllers::startScanningMode()
{
   NetworkScanningModel networkScanningModel;
   std::vector<std::string> activeHosts;
   activeHosts = networkScanningModel.getNetworkScan();

   std::cout << "Your list of active hosts\n";
   for (const auto& i : activeHosts) {
      std::cout << i << "\n";
   }

   std::cout << "To proceed press enter\n";
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   std::cin.get();
}