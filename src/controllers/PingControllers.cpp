#include "../include/controllers/PingControllers.hpp"

#include "../include/models/PingModel.hpp"

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

   int selectedSengingfPingMode {0};
   switch (static_cast<PingWorkingMode>(selectedOption)) {
      case PingWorkingMode::Manual:
         std::cout << "Warning if you wanna use this function you must run this app on sudo mode\n";
         std::cout << "Enter IP of ping destination\n";
         std::cin >> userInputIP;

         std::cout << "Do you wanna send multiple ping packets?\n";
         std::cout << "(1) Yes\n";
         std::cout << "(2) No\n";
         std::cin >> selectedSengingfPingMode;
         switch (static_cast<SendingPingMode>(selectedSengingfPingMode)) {
            case SendingPingMode::MultiSend:
               while (true) {
                  std::cout << "Ping sent\n";
                  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                  pingModel.sendPing(userInputIP);
               }
               break;

            case SendingPingMode::SingleSend:
               pingModel.sendPing(userInputIP);
               break;
         }

         break;
      case PingWorkingMode::Automatic:
         std::cout << "I don't implemented this function yet\n";
         std::this_thread::sleep_for(std::chrono::milliseconds(3000));
         break;
      default:
         break;
   }
}