#include "../include/controllers/PingControllers.hpp"

#include "../include/models/PingModel.hpp"

#include <chrono>
#include <iostream>
#include <thread>

enum class PingWorkingMode {
   Manual = 1,
   Automatic,
};

void PingControllers::startPingingMode()
{
   int selectedOption {0};

   std::cout << "You enter to ping mode\n";
   std::cout << "Select mode where you want to work\n";
   std::cout << "(1) Manual pinging mode\n";
   std::cout << "(2) Automatic pinging mode\n";
   std::cin >> selectedOption;

   std::string userInputIP {};
   PingModel pingModel {};

   switch (static_cast<PingWorkingMode>(selectedOption)) {
      case PingWorkingMode::Manual:
         std::cout << "Warning if you wanna use this function you must run this app on sudo mode\n";
         std::cout << "Enter IP of ping destination\n";
         std::cin >> userInputIP;
         pingModel.sendPing(userInputIP);
         break;
      case PingWorkingMode::Automatic:
         std::cout << "I don't implemented this function yet\n";
         std::this_thread::sleep_for(std::chrono::milliseconds(3000));
         break;
      default:
         break;
   }
}