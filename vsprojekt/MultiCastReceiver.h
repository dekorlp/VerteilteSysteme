/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiCastReceiver.h
 * Author: michael
 *
 * Created on 25. Mai 2017, 23:53
 */
// UPLOADED
#ifndef MULTICASTRECEIVER_H
#define MULTICASTRECEIVER_H

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"

using namespace std;

class MultiCastReceiver {
public:
    MultiCastReceiver(boost::asio::io_service& io_service,
            const boost::asio::ip::address& listen_address,
            const boost::asio::ip::address& multicast_address);
    
    std::string receive();

    void handle_receive_from(const boost::system::error_code& error,
            size_t bytes_recvd);

private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    const short multicast_port = 30001;
    const int max_length = 1024;
    char data_[1024];



};

#endif /* MULTICASTRECEIVER_H */

