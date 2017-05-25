#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <sstream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;
using namespace std; 
 
enum {
    max_length = 1024
};


vector<std::string> split(std::string str, char c) {
    vector<std::string> result;
    
    
    // Split Funktion EVTL. Fehler anfeallig, falls keine Zahl uebretragen wird.
   // cout << "IN SPLIT " << endl;
   // sleep(1);
            
    while (!str.empty() && str.size() > 1) {
        
        if(!isdigit(str.at(0))){
            break;
        }
        result.push_back(str.substr(0, str.find(c, 0)));
        str.erase(0, str.find(c, 0) + 1);
     //   cout << "str: " << str<< endl; 
      //  sleep(1);
    }
  
    return result;
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: blocking_udp_echo_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        udp::socket s(io_service, udp::endpoint(udp::v4(), 0));

        udp::resolver resolver(io_service);
        udp::resolver::query query(udp::v4(), argv[1], argv[2]);
        udp::resolver::iterator iterator = resolver.resolve(query);

       
        std::cout << "\n\nHello here are the sensor data: " << std::endl;
        char request[max_length] = "Hatem_Ist_ein_Baer_Im_Winterschlaf_:D";
       
        
        size_t request_length = strlen(request);
        s.send_to(boost::asio::buffer(request, request_length), *iterator);

        char reply[max_length];
        udp::endpoint sender_endpoint;
        size_t reply_length = s.receive_from(
                boost::asio::buffer((char*) reply, max_length), sender_endpoint);

        std::cout << "\nSensor Server Replay is: \n\n";

        
        cout << "REPLAY " << reply << endl;
        // Ausgabe Decoden
        vector<std::string> splittedSemacolons = split(std::string(reply), ';');

        
        for (string sOutput : splittedSemacolons) {
         
            
            std::cout << "Sensor ID     : " <<  sOutput.substr(0, sOutput.find('#', 0))<< std::endl;
            std::cout << "Sensor Value  : " <<  sOutput.substr(sOutput.find('#')+1, sOutput.size()-1)<< std::endl;
            std::cout << std::endl;

        }

        cout << "BEVOR SOCKET CLOSE " << endl;
        // Socket und io Service schliessen
        s.close();
        io_service.stop();
        
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}