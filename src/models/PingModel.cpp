#include "../include/models/PingModel.hpp"

#include "../../include/tools/computeChecksum.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <chrono>

using boost::asio::ip::icmp;

using ICMPPackagesDataType = std::shared_ptr<ICMPPackageData>;

void PingModel::sendPing(std::string destination_ip)
{
   boost::asio::io_context context;
   icmp::resolver resolver(context);
   auto endpoint              = resolver.resolve(icmp::v4(), destination_ip, "");
   icmp::endpoint destination = *endpoint.begin();
   icmp::socket socket(context, icmp::v4());

   const std::string packageBody {"Ping from MooPing"};
   auto startTime = std::chrono::steady_clock::now();
   socket.send_to(boost::asio::buffer(constructICMPPackage(packageBody)), destination);

   std::shared_ptr<ICMPPackageData> currentPackageData {std::make_shared<ICMPPackageData>()};
   boost::asio::streambuf replyBuffer;
   icmp::endpoint senderEndpoint;

   std::size_t length       = socket.receive_from(replyBuffer.prepare(1024), senderEndpoint);
   auto endTime             = std::chrono::steady_clock::now();
   auto duration            = std::chrono::duration<double, std::milli>(endTime - startTime);
   currentPackageData->time = duration.count();
   replyBuffer.commit(length);

   std::vector<unsigned char> rawData(boost::asio::buffers_begin(replyBuffer.data()),
                                      boost::asio::buffers_end(replyBuffer.data()));

   if (length >= 20) {
      unsigned char ttl       = rawData[8];
      currentPackageData->ttl = static_cast<int>(ttl);
   }

   currentPackageData->size               = sizeof(ICMPHeader) + packageBody.size();
   currentPackageData->sequenceNumber     = packageSequenceNumber;
   currentPackageData->destinationAddress = destination.address().to_string().c_str();

   ICMPPackagesData.push_back(currentPackageData);

   packageSequenceNumber++;
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

[[nodiscard]] std::vector<ICMPPackagesDataType> PingModel::getPackagesData()
{
   return ICMPPackagesData;
}