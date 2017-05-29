/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ShopConnection.h
 * Author: dennis
 *
 * Created on 29. Mai 2017, 10:13
 */

#ifndef SHOPCONNECTION_H
#define SHOPCONNECTION_H



#include "ShopConnection.h"
#include "gen-cpp/ShopRequest.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace std;//ShopRequestClient::ShopRequestClient(boost::shared_ptr<::apache::thrift::protocol::TProtocol> prot)

class ShopConnection
{
    private:
        boost::shared_ptr<TTransport> socket;
        boost::shared_ptr<TTransport> transport;
        boost::shared_ptr<TProtocol> protocol;
        ShopRequestClient client;
        
        //ShopRequestClient client;
        int price;
    public:
        ShopConnection();
        ShopConnection(string ipAdress);
        int requestProduct(int productId, int bestellMenge);
        ProductAnswer buyProduct(int productId, int bestellMenge);
        void setPrice(int price);
        int getPrice();
};


#endif /* SHOPCONNECTION_H */

