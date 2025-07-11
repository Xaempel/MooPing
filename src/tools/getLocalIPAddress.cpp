#include "../include/tools/getLocalIPAddress.hpp"

#include <boost/asio.hpp>

std::string tools::getLocalIPAddress()
{
   std::string IP {};

   boost::asio::io_context context;
   boost::asio::ip::tcp::resolver resolver(context);
   auto hostIPList = resolver.resolve(boost::asio::ip::host_name(), "");

   for (const auto& entry : hostIPList) {
      auto endPoint = entry.endpoint();

      if (endPoint.address().is_v4() && endPoint.address().to_string() != "127.0.0.1") {
         IP = endPoint.address().to_string();
         break;
      }
   }

   return IP;
}