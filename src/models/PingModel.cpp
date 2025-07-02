#include "../include/models/PingModel.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <cstdint>

using boost::asio::ip::icmp;

struct ICMPHeader {
   std::uint8_t type            = 8;
   std::uint8_t code            = 0;
   std::uint16_t checksum       = 0;
   std::uint16_t identifier     = 0;
   std::uint16_t sequenceNumber = 0;
};

// I added a sketch of ping function someday I'll make a checksum compute function and I'll more develop this function  
void PingModel::sendPing(std::string destination_ip)
{
   boost::asio::io_context context;

   icmp::resolver resolver(context);

   auto endpoint {resolver.resolve(icmp::v4(), destination_ip, "")};
   icmp::endpoint destination {*endpoint.begin()};

   icmp::socket socket(context, icmp::v4());

   ICMPHeader packageHeader;

   const std::string packageBody = "Ping from MooPing";

   std::vector<uint8_t> data(sizeof(ICMPHeader) + packageBody.size());
   std::memcpy(data.data(), &packageHeader, sizeof(ICMPHeader));
   std::memcpy(data.data() + sizeof(ICMPHeader), packageBody.data(), packageBody.size());

   socket.send_to(boost::asio::buffer(data), destination);
}