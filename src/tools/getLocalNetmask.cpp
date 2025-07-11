#include "../include/tools/getLocalNetmask.hpp"

// Windows Required Headers
#ifdef _WIN32

// Linux Required Headers
#else
#include <arpa/inet.h>
#include <ifaddrs.h>
#endif

std::string tools::getLinuxLocalNetmask()
{
   std::string netmask {};

#ifdef _WIN32
#error "This function is only for a Linux. Dudee! "
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