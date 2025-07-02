#include "../include/models/NetworkScanningModel.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <list>
#include <string>

void NetworkScanningModel::scanNetwork()
{
   std::string IP {};
   std::cout << "Input your ip address for scan a network\n";
   std::cout << "The input format must be like this x.x.x.x/z\n";
   std::cout << "Where x is a octet and z is a short mask\n";
   std::cin >> IP;
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

   std::string command {"nmap -sn " + IP + " -oX scan_result.xml > /dev/null 2>&1"};
   system(command.c_str());

   std::list<std::string> IPlist {};
   boost::property_tree::ptree tree {};
   boost::property_tree::read_xml("scan_result.xml", tree);

   for (const auto& node : tree.get_child("nmaprun")) {
      if (node.first == "host") {
         for (const auto& child : node.second) {
            if (child.first == "address") {
               std::string ip = child.second.get<std::string>("<xmlattr>.addr");
               IPlist.push_back(ip);
            }
         }
      }
   }

   std::cout << "Your list of active hosts\n";
   for (const auto& i : IPlist) {
      std::cout << i << "\n";
   }
   std::cout << "To proceed press enter\n";
   std::cin.get();
}