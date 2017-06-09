/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiCastReceiver.cpp
 * Author: michael
 * 
 * Created on 25. Mai 2017, 23:53
 */
// UPLOADED

//#include <bits/std_mutex.h>

#include "MultiCastReceiver.h"

MultiCastReceiver::MultiCastReceiver(boost::asio::io_service& io_service,
        const boost::asio::ip::address& listen_address,
        const boost::asio::ip::address& multicast_address,
        vector<int> &sensorList,
        mutex &mutex)
: socket_(io_service) {

    this->m = &mutex;
    
    this->sensorList = &sensorList;
    // Create the socket so that multiple may be bound to the same address.
    boost::asio::ip::udp::endpoint listen_endpoint(
            listen_address, multicast_port);
    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);
 
    // Join the multicast group.
    socket_.set_option(
            boost::asio::ip::multicast::join_group(multicast_address));

    // Für Lokal Rechner
    socket_.set_option(boost::asio::ip::multicast::enable_loopback(true));

 
    socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), sender_endpoint_,
            boost::bind(&MultiCastReceiver::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

}

void MultiCastReceiver::decodeMessage(string message)
{
    if(message.find("#", 0) != -1)
    {
        // 3#85;;;;
        // 11#100
        // 0123456789
        int sensorNr;
        int sensorValue;
        
        sensorNr = stoi(message.substr(0, message.find("#", 0)));
        
        message.erase(0, message.find("#", 0)+1);
        sensorValue = stoi(message.substr(0, message.find(";", 0)));
        
        
        m->lock();
        sensorList->at(sensorNr) = sensorValue;
        cout << "\nSensor Nr. " << sensorNr << "  Value AUFGEFÜLLT: " << sensorValue <<endl;

        m->unlock();
        
        
    }
}

void MultiCastReceiver::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd) {


    if (!error) {
        
        
        decodeMessage(data_);
        
       
       
        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&MultiCastReceiver::handle_receive_from, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}
