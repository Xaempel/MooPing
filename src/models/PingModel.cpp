#include "../include/models/PingModel.hpp"

#include "../../include/tools/computeChecksum.hpp"

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

   if (length >= 20) {
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