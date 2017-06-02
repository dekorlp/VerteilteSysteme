/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on 25. Mai 2017, 13:58
 */

// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "gen-cpp/ShopRequest.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <iostream>
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

int sensorPrice1 = 2;
int sensorPrice2 = 5;
int sensorPrice3 = 3;
int sensorPrice4 = 4;

Bill bill;

class ShopRequestHandler : virtual public ShopRequestIf {
public:

    ShopRequestHandler() {
        // Your initialization goes here
    }
    
    int32_t requestProduct(const int32_t sendorId, const int32_t bestellMenge) {
        // Your implementation goes here
        int price;

        switch (sendorId) {
            case(0):
                        price = sensorPrice1;
                break;
            case(1):
                        price = sensorPrice2;
                break;
            case(2):
                        price = sensorPrice3;
                break;
            case(3):
                        price = sensorPrice4;
        }
        
        printf("requestProduct\n");
        return price;
    }

    void buyProducts(ProductAnswer& _return, const int32_t sendorId, const int32_t bestellMenge) {
        // Your implementation goes here

        ProductAnswer pA;
     

        pA.sensorId = sendorId;
        pA.menge = bestellMenge;
        switch (sendorId) {
            case(0):
                        pA.preis = sensorPrice1;
                break;
            case(1):
                        pA.preis = sensorPrice2;
                break;
            case(2):
                        pA.preis = sensorPrice3;
                break;
            case(3):
                        pA.preis = sensorPrice4;
        }

       
        bill.produkte.push_back(pA);
        _return = pA;
        
        printf("buyProducts\n");
    }

    void getBill(Bill& _return) {
        // Your implementation goes here
        _return = bill;
        printf("getBill\n");
    }

    void ping() {
        // Your implementation goes here
        printf("ping\n");
    }

};

int main(int argc, char **argv) {
    
    std::cout << "Preis für Sensor 1: ";
    std::cin >> sensorPrice1;
    std::cout << std::endl;
    
    std::cout << "Preis für Sensor 2: ";
    std::cin >> sensorPrice2;
    std::cout << std::endl;
    
    std::cout << "Preis für Sensor 3: ";
    std::cin >> sensorPrice3;
    std::cout << std::endl;
    
    std::cout << "Preis für Sensor 4: ";
    std::cin >> sensorPrice4;
    std::cout << std::endl;
    
    int port = 9090;
    shared_ptr<ShopRequestHandler> handler(new ShopRequestHandler());
    shared_ptr<TProcessor> processor(new ShopRequestProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
    return 0;
}

