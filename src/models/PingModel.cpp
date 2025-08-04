#include "../include/models/PingModel.hpp"

#include "../../include/tools/computeChecksum.hpp"

#include <boost/asio/ip/icmp.hpp>
#include <stdexcept>

using boost::asio::ip::icmp;

using ICMPPackagesDataType = std::shared_ptr<ICMPPackageData>;

PingModel::PingModel()
    : _socket(_context, icmp::v4())
{
}

void PingModel::sendPing(std::string destination_ip)
{
   icmp::resolver resolver(_context);
   auto endpoint              = resolver.resolve(icmp::v4(), destination_ip, "");
   icmp::endpoint destination = *endpoint.begin();
   destinationAddress         = destination.address().to_string();

   _startTime = std::chrono::steady_clock::now();
   _socket.send_to(boost::asio::buffer(constructICMPPackage(_packageBody)), destination);
}

[[nodiscard]] ICMPPackagesDataType PingModel::receivePing()
{
   std::shared_ptr<ICMPPackageData> currentPackageData {std::make_shared<ICMPPackageData>()};
   boost::asio::streambuf replyBuffer;
   icmp::endpoint senderEndpoint;

   std::size_t length = _socket.receive_from(replyBuffer.prepare(1024), senderEndpoint);
   replyBuffer.commit(length);

   auto endTime             = std::chrono::steady_clock::now();
   auto duration            = std::chrono::duration<double, std::milli>(endTime - _startTime);
   currentPackageData->time = duration.count();

   std::vector<unsigned char> rawData(boost::asio::buffers_begin(replyBuffer.data()),
                                      boost::asio::buffers_end(replyBuffer.data()));

   uint8_t ipHeaderLength = (rawData[0] & 0x0F) * 4;
   const uint8_t icmpHeaderLength {8};

   if (length >= ipHeaderLength + icmpHeaderLength) {
      unsigned char icmpType = rawData[ipHeaderLength];
      unsigned char icmpCode = rawData[ipHeaderLength + 1];

      constexpr int destinationUnreachable {3};
      if (icmpType == destinationUnreachable) {
         constexpr int networkUnreachable {0};
         constexpr int hostUnreachable {1};
         
         if (icmpCode == networkUnreachable) {
            throw std::runtime_error("Network Unreachable");
         }
         else if (icmpCode == hostUnreachable) {
            throw std::runtime_error("Host Unreachable");
         }
         else {
            throw std::runtime_error("Destination Unreachable");
         }
      }

      unsigned char ttl       = rawData[8];
      currentPackageData->ttl = static_cast<int>(ttl);
   }

   currentPackageData->size               = sizeof(ICMPHeader) + _packageBody.size();
   currentPackageData->sequenceNumber     = packageSequenceNumber;
   currentPackageData->destinationAddress = destinationAddress;

   packageSequenceNumber++;
   return currentPackageData;
}

std::vector<uint8_t> PingModel::constructICMPPackage(const std::string body)
{
   ICMPHeader packageHeader;
   packageHeader.type           = 8;
   packageHeader.code           = 0;
   packageHeader.identifier     = htons(1);
   packageHeader.sequenceNumber = htons(packageSequenceNumber);

   std::vector<uint8_t> data(sizeof(ICMPHeader) + body.size());

   std::memcpy(data.data(), &packageHeader, sizeof(ICMPHeader));
   std::memcpy(data.data() + sizeof(ICMPHeader), body.data(), body.size());

   uint16_t checksum      = tools::computeChecksum(data.data(), data.size());
   packageHeader.checksum = htons(checksum);

   std::memcpy(data.data(), &packageHeader, sizeof(ICMPHeader));

   return data;
}