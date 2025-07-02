#include "../include/controllers/NetworkScanningControllers.hpp"

void NetworkScanningControllers::startScanningMode()
{
   NetworkScanningModel networkScanningModel;
   networkScanningModel.scanNetwork();
}