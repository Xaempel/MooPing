#include "../include/controllers/PingControllers.hpp"

#include <chrono>
#include <iostream>
#include <thread>

void PingControllers::startPiningMode()
{
   std::cout << "You enter to ping mode\n";
   std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}