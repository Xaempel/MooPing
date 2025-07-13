#include "../include/models/NetworkScanningModel.hpp"

#include "../include/tools/getLocalIPAddress.hpp"
#include "../include/tools/getLocalNetmask.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>

std::vector<std::string> NetworkScanningModel::getNetworkScan()
{
   std::vector<std::string> networkScan;

   std::string ip {tools::getLocalIPAddress()};
   std::string mask {tools::getLinuxLocalNetmask()};

   std::string command = "nmap -sn " + ip + "/" + mask + " -oX scan_result.xml > /dev/null 2>&1";
   system(command.c_str());

   boost::property_tree::ptree tree {};
   boost::property_tree::read_xml("scan_result.xml", tree);

   for (const auto& node : tree.get_child("nmaprun")) {
      if (node.first == "host") {
         for (const auto& child : node.second) {
            if (child.first == "address") {
               std::string addressType = child.second.get<std::string>("<xmlattr>.addrtype");

               if (addressType == "ipv4") {
                  std::string ip = child.second.get<std::string>("<xmlattr>.addr");
                  networkScan.push_back(ip);
               }
            }
         }
      }
   }

   return networkScan;
}