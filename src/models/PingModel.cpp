#include "../include/models/PingModel.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <cstdint>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif

using boost::asio::ip::icmp;

struct ICMPHeader {
   std::uint8_t type            = 8;
   std::uint8_t code            = 0;
   std::uint16_t checksum       = 0;
   std::uint16_t identifier     = 0;
   std::uint16_t sequenceNumber = 0;
};

uint16_t computeChecksum(const uint8_t* data, std::size_t length)
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

void PingModel::sendPing(std::string destination_ip)
{
#ifdef _WIN32
   WSADATA wsaData;
   if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
      throw std::runtime_error("WSAStartup failed");
   }
#endif

   boost::asio::io_context context;
   icmp::resolver resolver(context);
   auto endpoint              = resolver.resolve(icmp::v4(), destination_ip, "");
   icmp::endpoint destination = *endpoint.begin();
   icmp::socket socket(context, icmp::v4());

   ICMPHeader packageHeader;
   packageHeader.type           = 8;
   packageHeader.code           = 0;
   packageHeader.identifier     = htons(1);
   packageHeader.sequenceNumber = htons(1);

   const std::string packageBody = "Ping from MooPing";
   std::vector<uint8_t> data(sizeof(ICMPHeader) + packageBody.size());

   std::memcpy(data.data(), &packageHeader, sizeof(ICMPHeader));
   std::memcpy(data.data() + sizeof(ICMPHeader), packageBody.data(), packageBody.size());

   uint16_t checksum      = computeChecksum(data.data(), data.size());
   packageHeader.checksum = htons(checksum);

   std::memcpy(data.data(), &packageHeader, sizeof(ICMPHeader));

   socket.send_to(boost::asio::buffer(data), destination);

#ifdef _WIN32
   WSACleanup();
#endif
}