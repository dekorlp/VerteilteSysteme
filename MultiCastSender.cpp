//
// sender.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//#include <bits/std_mutex.h>

#include "MultiCastSender.h"

MultiCastSender::MultiCastSender(boost::asio::io_service& io_service,
        const boost::asio::ip::address& multicast_address,
        vector<ProductAnswer>& orderList,
        mutex &mutex)
: endpoint_(multicast_address, multicast_port),
socket_(io_service, endpoint_.protocol()),
timer_(io_service),
message_count_(0) {
    this->orderList = &orderList;
    this->m = &mutex;

     boost::system::error_code ec;
    
    send_routine(ec);
}

void MultiCastSender::send_routine(const boost::system::error_code& error) {
    //cout << "SEND ROUTINE AUFRUF" << endl;
    if (!error) {
        //cout << "SEND FOR ORDER LIST " << orderList->size() <<endl;
        if (orderList->size() > 0) {
            m->lock();
            char cRequest[1024] = "";
            string message = encodeMessage(orderList->at(orderList->size() - 1));
            
            strcat(cRequest, message.c_str());
            size_t request_length = message.size();
            
            orderList->pop_back();
            m->unlock();
            //cout << "Server sendet" << cRequest << endl;
            socket_.async_send_to(
                    boost::asio::buffer(cRequest, request_length), endpoint_,
                    boost::bind(&MultiCastSender::send_routine, this,
                    boost::asio::placeholders::error));
        } else {
            timer_.expires_from_now(boost::posix_time::seconds(3));
            timer_.async_wait(
            boost::bind(&MultiCastSender::send_routine, this,
                    boost::asio::placeholders::error));
        }
    }


}

string MultiCastSender::encodeMessage(ProductAnswer productAnswer) {

    stringstream sbuffer;
    sbuffer << productAnswer.sensorId;
    sbuffer << "#";
    sbuffer << productAnswer.menge;
    sbuffer << ";;;;\0";

    return sbuffer.str();

    /* char cRequest[1024] = "";
     strcat(cRequest, sbuffer.str().c_str());
     size_t request_length = sbuffer.str().size();

     cout << "THRIFT THREAD !!!!!!!!!!!!!!!!!!\n\n" << sbuffer.str() << "\n" << endl;
     cout << "Bestellmenge :" << bestellMenge << endl;*/



}

void MultiCastSender::handle_send_to(const boost::system::error_code& error) {
    if (!error && message_count_ < max_message_count) {
        timer_.expires_from_now(boost::posix_time::seconds(1));
        timer_.async_wait(
                boost::bind(&MultiCastSender::handle_timeout, this,
                boost::asio::placeholders::error));
    }
}

void MultiCastSender::handle_timeout(const boost::system::error_code& error) {
    if (!error) {
        std::ostringstream os;
        os << "Message " << message_count_++;
        message_ = os.str();

        socket_.async_send_to(
                boost::asio::buffer(message_), endpoint_,
                boost::bind(&MultiCastSender::handle_send_to, this,
                boost::asio::placeholders::error));
    }
}