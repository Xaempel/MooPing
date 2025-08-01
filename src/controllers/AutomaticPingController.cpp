#include "../../include/controllers/AutomaticPingController.hpp"

#include "../../include/models/NetworkScanningModel.hpp"

#include <iostream>
#include <string>
#include <vector>

AutomaticPingController::AutomaticPingController(PingModel& pingModel)
    : _pingModel(pingModel)
{
}

void AutomaticPingController::startAutomaticPingMode()
{
   NetworkScanningModel networkScanningModel {};

   std::vector<std::string> activeDeviseList = networkScanningModel.getNetworkScan();

   int hostsCounter {1};
   std::cout << "Your list of active host in network\n";
   for (auto i : activeDeviseList) {
      std::cout << "(" << hostsCounter << ") " << i << std::flush << "\n";
      hostsCounter++;
   }
   int selectedHost {0};
   std::cout << "Whose host I have to send a ping?\n";
   std::cin >> selectedHost;

   if (selectedHost > 0 && selectedHost - 1 < activeDeviseList.size()) {
      _pingModel.sendPing(activeDeviseList.at(selectedHost - 1));
   }
}