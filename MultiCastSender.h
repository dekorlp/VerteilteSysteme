/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiCastSender.h
 * Author: michael
 *
 * Created on 25. Mai 2017, 22:37
 */

#ifndef MULTICASTSENDER_H
#define MULTICASTSENDER_H

#include <boost/asio.hpp>
#include <iostream>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

class MultiCastSender {
public:
    MultiCastSender(boost::asio::io_service& io_service,
            const boost::asio::ip::address& multicast_address);
    void send(std::string message);
    void handle_send_to(const boost::system::error_code &error);
    void handle_timeout(const boost::system::error_code &error);
    

private:
    boost::asio::ip::udp::endpoint endpoint_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::deadline_timer timer_;
    int message_count_;
    std::string message_;
    const short multicast_port = 30001;
    const int max_message_count = 10;
    const int max_length = 1024;
};

#endif /* MULTICASTSENDER_H */

