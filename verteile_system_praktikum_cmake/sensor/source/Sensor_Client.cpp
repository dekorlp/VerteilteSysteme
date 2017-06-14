//
// blocking_udp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// UPLOADED
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>

#include "MultiCastReceiver.h"

using namespace std;
using boost::asio::ip::udp;

const int numberOfSensors = 4;

enum {
    max_length = 1024
};

std::mutex m;
std::mutex mm;

// restart Sensors setzt Sensoren auf 100 zurück

void refillSensors(vector<int> &SensorValueList) {
    string ipMulticast = "224.0.0.1";
    string netzmaske = "0.0.0.0";
    //SensorValueList.at(2) = 50;
    
    boost::asio::io_service io_service;
    MultiCastReceiver r(io_service,
            boost::asio::ip::address::from_string(netzmaske),
            boost::asio::ip::address::from_string(ipMulticast),
            SensorValueList,
            m);
    io_service.run();
}

void newCoutThread(vector<int> &SensorValueList) {
    //cout << "\n\nHEllo World !!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n" << endl;
    while(true)
        {
            int i = 0;
            cout << "SIZE: " << SensorValueList.size()<<endl;;
            for(int element : SensorValueList)
            {
                
            
                 i++;
            }
            sleep(3);
        }
}

void sensorThread(int sensorNr, int reduceProz, char* argv[], vector<int> &SensorValueList) {

    boost::asio::io_service io_service;

    udp::socket s(io_service, udp::endpoint(udp::v4(), 0));

    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), argv[1], argv[2]);
    udp::resolver::iterator iterator = resolver.resolve(query);


    while (true) {
        m.lock();
        //system("sl");
        std::cout << "Sensor Nr. [" << sensorNr << "] " << "says: " <<  SensorValueList.at(sensorNr) << std::endl;
        std::cout.flush();

        //////////// Sende /////////////////

        char cRequest[1024] = "";
        std::stringstream stringBuilder;
        stringBuilder << sensorNr << "#" << SensorValueList.at(sensorNr) << '\0';
        strcat(cRequest, stringBuilder.str().c_str());

        size_t request_length = stringBuilder.str().size();


        s.send_to(boost::asio::buffer(cRequest, request_length), *iterator);

        /////////// Sende Ende/////////////////

        if (SensorValueList.at(sensorNr) <= 0 || SensorValueList.at(sensorNr) <= reduceProz) {
            SensorValueList.at(sensorNr) = 0;
            //            countIfzero--;

           
        } else if (SensorValueList.at(sensorNr) > 0) {
            SensorValueList.at(sensorNr) = SensorValueList.at(sensorNr) - reduceProz;
        }

        m.unlock();
        sleep(3);
    }
}

int main(int argc, char* argv[]) {


    vector<int> SensorValueList;



    try {
        if (argc != 3) {
            std::cerr << "Usage: blocking_udp_echo_client <host> <port>\n";
            return 1;
        }




        srand(time(NULL));
        thread t[numberOfSensors];
        thread refillThread;


        for (int i = 0; i < numberOfSensors; i++) {
            SensorValueList.push_back(100);
            t[i] = std::thread(sensorThread, i, (rand() % 20 + 1), argv,std::ref(SensorValueList));
        }
        refillThread = std::thread(refillSensors,std::ref(SensorValueList));

     
     
        for (int i = 0; i < numberOfSensors; i++) {
            t[i].join();
        }

      
        
        
        refillThread.join();



    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }




    return 0;
}
