#include "../../include/tools/computeChecksum.hpp"

uint16_t tools::computeChecksum(const uint8_t* data, std::size_t length)
{
   uint32_t sum = 0;

   for (std::size_t i = 0; i + 1 < length; i += 2) {
      uint16_t word = (data[i] << 8) + data[i + 1];
      sum += word;
   }

   if (length % 2 == 1) {
      uint16_t word = data[length - 1] << 8;
      sum += word;
   }

   while (sum >> 16) {
      sum = (sum & 0xFFFF) + (sum >> 16);
   }

   return static_cast<uint16_t>(~sum);
}