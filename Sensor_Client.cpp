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

void refillSensorValue(int &sensorValue, int sensorNr) {

    cout << "IN REFILL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << endl;

    string ipMulticast = "224.0.0.1";
    string netzmaske = "0.0.0.0";

    boost::asio::io_service io_service;
    MultiCastReceiver r(io_service,
            boost::asio::ip::address::from_string(netzmaske),
            boost::asio::ip::address::from_string(ipMulticast));
    io_service.run();

    //string test = r.receive();

    /*cout << test << endl;
    if (test.size() >= 3) {
        cout << "IN REFILL IF ABFRAGE" << endl;
        cout << test << endl;

    }*/

}

void sensorThread(int sensorNr, int reduceProz, char* argv[]) {
    int sensorValue = 100;

    boost::asio::io_service io_service;

    udp::socket s(io_service, udp::endpoint(udp::v4(), 0));

    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), argv[1], argv[2]);
    udp::resolver::iterator iterator = resolver.resolve(query);

    

    while (true) {
        m.lock();
        //system("sl");
        std::cout << "Sensor Nr. [" << sensorNr << "] " << "says: " << sensorValue << std::endl;

        //////////// Sende /////////////////

        char cRequest[1024] = "";
        std::stringstream stringBuilder;
        stringBuilder << sensorNr << "#" << sensorValue << '\0';
        strcat(cRequest, stringBuilder.str().c_str());

        size_t request_length = stringBuilder.str().size();

        //    cout << "Sensor AUSGABE BEVOR SENDEN" << stringBuilder.str() << endl; 
        s.send_to(boost::asio::buffer(cRequest, request_length), *iterator);

        /////////// Sende Ende/////////////////
        if (sensorValue <= 20) {
            cout << "BIN BALD LEER " << endl;
            
            sensorValue = 200;
        }

        if (sensorValue <= 0 || sensorValue <= reduceProz) {
            sensorValue = 0;
            //            countIfzero--;
            if (1 == 0) {
                // Recaive Thread

            }
        } else if (sensorValue > 0) {
            sensorValue = sensorValue - reduceProz;
        }

        m.unlock();
        sleep(2);
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: blocking_udp_echo_client <host> <port>\n";
            return 1;
        }

        /*        std::thread t[4];
                //    std::thread sender;

                //for(int i = 0; i < 4; i++){
                t[0] = std::thread(sensorThread, 0, 5, argv);
                t[1] = std::thread(sensorThread, 1, 3, argv);
                t[2] = std::thread(sensorThread, 2, 10, argv);
                t[3] = std::thread(sensorThread, 3, 20, argv);
                //        sender = std::thread(senderThread, argv);
                //}

                for (int i = 0; i < 4; i++) {
                    t[i].join();
                }
                //        sender.join();
         */
        int i = 100;
        thread receiveThread;

            receiveThread = thread(refillSensorValue, std::ref(i), 2);

            receiveThread.join();
        
        
        srand(time(NULL));
        thread t[numberOfSensors];

        for (int i = 0; i < numberOfSensors; i++) {
            t[i] = std::thread(sensorThread, i, (rand() % 20 + 1), argv);
        }

        for (int i = 0; i < numberOfSensors; i++) {
            t[i].join();
        }

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }




    return 0;
}
