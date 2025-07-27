#include "../include/tools/getLocalNetmask.hpp"

#include <stdexcept>

// Windows Required Headers
#ifdef _WIN32
#include <windows.h>
#include <iphlpapi.h>
#include <vector>
#include <stdexcept>
#include <iostream>
// Linux Required Headers
#else
#include <arpa/inet.h>
#include <ifaddrs.h>
#endif

std::string tools::getLinuxLocalNetmask()
{
   std::string netmask {};

#ifdef _WIN32
   throw std::runtime_error("This function is only for a Linux. Dudee!");
#else

   struct ifaddrs* ifaddr;
   struct ifaddrs* ifa;

   getifaddrs(&ifaddr);

   for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
      if (ifa->ifa_addr == nullptr) {
         continue;
      }

      if (ifa->ifa_addr->sa_family == AF_INET && std::string(ifa->ifa_name) != "lo") {
         auto selectedMask {reinterpret_cast<sockaddr_in*>(ifa->ifa_netmask)};
         uint32_t binaryMask {ntohl(selectedMask->sin_addr.s_addr)};

         int count {0};
         for (int i = 31; i >= 0; i--) {
            if (binaryMask & (1 << i)) {
               count++;
            }
            else {
               break;
            }
         }
         netmask = std::to_string(count);
         break;
      }
   }
   freeifaddrs(ifaddr);
#endif

   return netmask;
}

std::string tools::getWindowsLocalNetmask()
{
#ifdef _WIN32
   ULONG buflen = 0;
   GetAdaptersInfo(nullptr, &buflen);

   std::vector<BYTE> buffer(buflen);
   PIP_ADAPTER_INFO adapterInfo = reinterpret_cast<PIP_ADAPTER_INFO>(buffer.data());

   if (GetAdaptersInfo(adapterInfo, &buflen) != ERROR_SUCCESS) {
      return {};
   }

   for (PIP_ADAPTER_INFO adapter = adapterInfo; adapter != nullptr; adapter = adapter->Next) {
      IP_ADDR_STRING* ipList = &adapter->IpAddressList;

      while (ipList) {
         const char* ipAddr = ipList->IpAddress.String;
         const char* mask   = ipList->IpMask.String;

         if (ipAddr && strcmp(ipAddr, "0.0.0.0") != 0 && strcmp(ipAddr, "127.0.0.1") != 0) {
            return std::string(mask);
         }
         ipList = ipList->Next;
      }
   }

   return {};
#else
   throw std::runtime_error("This function is only for Windows. Mate!");
#endif
}