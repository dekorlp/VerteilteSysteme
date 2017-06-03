//
// sender.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// UPLOADED
#include <iostream>
#include <sstream>
#include <string>

#include "MultiCastSender.h"
using namespace std;

MultiCastSender::MultiCastSender(boost::asio::io_service& io_service,
        const boost::asio::ip::address& multicast_address)
: endpoint_(multicast_address, multicast_port),
socket_(io_service, endpoint_.protocol()),
timer_(io_service),
message_count_(0) {
}

void MultiCastSender::send(std::string message) {

    char request[max_length];
    char * request2;
    std::stringstream ss;
    ss.clear();
    ss << message;
    ss << "\0";


    const size_t MAX = 1024;
    char chrs[MAX];

    memset(chrs, '\0', MAX);
    message.copy(chrs, MAX - 1);

//    strcat(request, ss.str().c_str());

//    size_t request_length = (ss.str().size());

    /*    std::cout << "MULTICAST SEND() message   : \n\n" << message << std::endl;
        std::cout << "MULTICAST SEND() lenght    : \n\n" << message.size() << std::endl;

        std::cout << "MULTICAST SEND() ss        : \n\n" << ss.str() << std::endl;
        std::cout << "MULTICAST SEND() lenght    : \n\n" << ss.str().size() << std::endl;

        std::cout << "MULTICAST SEND() request   : \n\n" << request << std::endl;
        std::cout << "MULTICAST SEND() lenght    : \n\n" << request_length << std::endl;
     */
    std::cout << "MULTICAST SEND() chrs   : \n\n" << chrs << std::endl;
    std::cout << "MULTICAST SEND() lenght    : \n\n" << (strlen(chrs)) << std::endl;

    socket_.async_send_to(
            boost::asio::buffer(chrs, max_length), endpoint_,
            boost::bind(&MultiCastSender::handle_send_to, this,
            boost::asio::placeholders::error));
}

void MultiCastSender::handle_send_to(const boost::system::error_code& error) {
    cout << "HANDLE SEND TO " << endl;
    if (!error ) {
        cout << "HANDLE SEND TO NO ERROR" << endl;
        timer_.expires_from_now(boost::posix_time::seconds(1));
        timer_.async_wait(
                boost::bind(&MultiCastSender::handle_timeout, this,
                boost::asio::placeholders::error));
    }else{
        cout << "HANDLE SEND TO ERROR" << endl;
    }
}

void MultiCastSender::handle_timeout(const boost::system::error_code& error) {
    cout << "HANDLE TIMEOUT" << endl;
    if (!error) {
        cout << "HANDLE TIMEOUT NO ERROR" << endl;
        std::ostringstream os;
        os << "Message " << message_count_++;
        message_ = os.str();

        socket_.async_send_to(
                boost::asio::buffer(message_), endpoint_,
                boost::bind(&MultiCastSender::handle_send_to, this,
                boost::asio::placeholders::error));
    }else{
        cout << "HANDLE TIMEOUT ERROR" << endl;
    }
}

