#include "../include/controllers/ScanningControllers.hpp"

#include <chrono>
#include <iostream>
#include <thread>

void ScanningControllers::startScanningMode()
{
   std::cout << "You enter to scanning mode\n";
   std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}