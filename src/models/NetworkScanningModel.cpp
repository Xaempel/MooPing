#include "../include/models/NetworkScanningModel.hpp"

#include "../include/tools/getLocalIPAddress.hpp"
#include "../include/tools/getLocalNetmask.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <list>
#include <string>

void NetworkScanningModel::scanNetwork()
{
   std::string IP = tools::getLocalIPAddress();
   std::string netmask {""};

#ifdef _WIN32

#else // code for Linux
   netmask = tools::getLinuxLocalNetmask();
#endif

   std::string command {"nmap -sn " + IP + "/" + netmask + " -oX scan_result.xml > /dev/null 2>&1"};
   system(command.c_str());

   std::list<std::string> IPlist {};
   boost::property_tree::ptree tree {};
   boost::property_tree::read_xml("scan_result.xml", tree);

   for (const auto& node : tree.get_child("nmaprun")) {
      if (node.first == "host") {
         for (const auto& child : node.second) {
            if (child.first == "address") {
               std::string addressType = child.second.get<std::string>("<xmlattr>.addrtype");

               if (addressType == "ipv4") {
                  std::string ip = child.second.get<std::string>("<xmlattr>.addr");
                  IPlist.push_back(ip);
               }
            }
         }
      }
   }

   std::cout << "Your list of active hosts\n";
   for (const auto& i : IPlist) {
      std::cout << i << "\n";
   }
   std::cout << "To proceed press enter\n";
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   std::cin.get();
}

std::vector<std::string> NetworkScanningModel::getNetworkScan(std::string IP)
{
   std::vector<std::string> networkScan;

   std::string command = "nmap -sn " + IP + " -oX scan_result.xml > /dev/null 2>&1";
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