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
    //cout << "GEH ST DU REIN? :)" << endl;
    // Join the multicast group.
    socket_.set_option(
            boost::asio::ip::multicast::join_group(multicast_address));

    // Für Lokal Rechner
    socket_.set_option(boost::asio::ip::multicast::enable_loopback(true));

    //cout << "Port adr:" << multicast_port << endl;
    //cout << "lisen cast adr:" << listen_address.to_string() << endl;
    //cout << "Multi cast adr:" << multicast_address.to_string() << endl;

    //cout << "BEFORE RECEIVE " << endl;
    socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), sender_endpoint_,
            boost::bind(&MultiCastReceiver::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

    //cout << "AFTER RECEIVE " << endl;
}

void MultiCastReceiver::decodeMessage(string message)
{
    if(message.find("#", 0) != -1)
    {
        // 3#85;;;;
        // 11#100
        // 0123456789
        //cout << "Nachricht ist gültig (# gefunden)" << endl;
        //cout << "decodeMessage: "<< message << endl;
        int sensorNr;
        int sensorValue;
        
        sensorNr = stoi(message.substr(0, message.find("#", 0)));
        
        message.erase(0, message.find("#", 0)+1);
        sensorValue = stoi(message.substr(0, message.find(";", 0)));
        
        //cout << "SENSOR NR "<< sensorNr<< endl;
        //cout << "SENSOR VALUEEE "<< sensorValue<< endl;
        
        m->lock();
        sensorList->at(sensorNr) = sensorValue;
        m->unlock();
        
        
    }
}

void MultiCastReceiver::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd) {

    //cout << "IN HANDLE RECEIVE FROM " << endl;


    if (!error) {
        //cout << "IN HANDLE RECEIVE FROM != ERROR" << endl;
        
        
        decodeMessage(data_);
        
        //sensorList->at(2) = 40;
       
        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&MultiCastReceiver::handle_receive_from, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}