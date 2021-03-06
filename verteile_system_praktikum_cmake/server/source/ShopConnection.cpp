/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <boost/array.hpp>
#include <string>
#include <iostream>


#include"ShopConnection.h"

#include "../gen-cpp/ShopRequest.h"


ShopConnection::ShopConnection()
   : client( NULL )
{
    
    this->socket = nullptr;
    this->transport = nullptr;
    this->protocol = nullptr;
}

ShopConnection::ShopConnection(string ipAdress)
: client(NULL){
    std::cout << "SHOP CONNECTION KONSTRUKTOR : IP: " << ipAdress<< std::endl;
    
    socket = boost::shared_ptr<TTransport>(new TSocket(ipAdress, 9090));
    transport = boost::shared_ptr<TTransport>(new TBufferedTransport(socket));
    protocol =  boost::shared_ptr<TProtocol>(new TBinaryProtocol(transport));
    client = ShopRequestClient(protocol);
    this->ipAdress = ipAdress;
}

int ShopConnection::requestProduct(int productId, int bestellMenge)
{
    int price = 0;
    transport->open();
    price = client.requestProduct(productId, bestellMenge);
    transport->close();
    return price;
}

ProductAnswer ShopConnection::buyProduct(int productId, int bestellMenge)
{
    ProductAnswer answer;
    
    transport->open();
    client.buyProducts(answer, productId, bestellMenge);
    transport->close();
    return answer;
}

string ShopConnection::getIpAdress()
{
    return ipAdress;
}

Bill ShopConnection::getBill()
{
    Bill bill;
    
    transport->open();
    client.getBill(bill);
    transport->close();
    return bill;
}

void ShopConnection::setPrice(int price)
{
    this->price = price;
}

int ShopConnection::getPrice()
{
    return this->price;
}
