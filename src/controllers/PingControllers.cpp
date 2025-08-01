#include "../include/controllers/PingControllers.hpp"

#include <chrono>
#include <iostream>
#include <thread>

enum class PingWorkingMode {
   Manual = 1,
   Automatic,
};

// Multi send mode - It's ping package is sending for infinity
enum class SendingPingMode {
   MultiSend = 1,
   SingleSend,
};

PingControllers::PingControllers() : automaticPingController(pingModel){}

void PingControllers::startPingingMode()
{
   int selectedOption {0};

   std::cout << "You enter to ping mode\n";
   std::cout << "Select mode where you want to work\n";
   std::cout << "(1) Manual pinging mode\n";
   std::cout << "(2) Automatic pinging mode\n";
   std::cin >> selectedOption;

   std::string userInputIP {};

   int selectedSengingfPingMode {0};

   PingWorkingMode convertSelectedOption = static_cast<PingWorkingMode>(selectedOption);
   if (convertSelectedOption == PingWorkingMode::Manual) {
      std::cout << "Warning if you wanna use this function you must run this app on sudo mode\n";
      std::cout << "Enter IP of ping destination\n";
      std::cin >> userInputIP;

      const auto additionalOptionInfoTextSelect = [] {
         std::cout << "(1) Yes\n";
         std::cout << "(2) No\n";
      };

      std::cout << "Do you wanna send multiple ping packets?\n";
      additionalOptionInfoTextSelect();
      std::cin >> selectedSengingfPingMode;

      const int enableAdditionalPackagesInfo {1};
      int additionalPackagesInfoOption {};
      std::cout << "Do you wanna see a packages info?\n";
      additionalOptionInfoTextSelect();
      std::cin >> additionalPackagesInfoOption;

      if (additionalPackagesInfoOption == enableAdditionalPackagesInfo) {
         isAdditionalInfoAboutPackages = true;
      }

      int currentPackageId {0};
      switch (static_cast<SendingPingMode>(selectedSengingfPingMode)) {
         case SendingPingMode::MultiSend:
            while (true) {
               std::this_thread::sleep_for(std::chrono::milliseconds(2000));
               pingModel.sendPing(userInputIP);
               if (isAdditionalInfoAboutPackages == true) {
                  auto ICMPPackagesData = pingModel.getPackagesData();
                  std::cout << "packages_size=" << ICMPPackagesData.at(currentPackageId)->size << "   ";
                  std::cout << "sequence_number=" << ICMPPackagesData.at(currentPackageId)->sequenceNumber << "   ";
                  std::cout << "ttl=" << ICMPPackagesData.at(currentPackageId)->ttl << "   ";
                  std::cout << "time=" << ICMPPackagesData.at(currentPackageId)->time << "ms    ";
                  std::cout << "destination_ip=" << ICMPPackagesData.at(currentPackageId)->destinationAddress << "  ";
                  std::cout << "\n";
                  currentPackageId++;
               }
            }
            break;

         case SendingPingMode::SingleSend:
            pingModel.sendPing(userInputIP);
            break;
      }
   }
   else {
      automaticPingController.startAutomaticPingMode();
   }
}