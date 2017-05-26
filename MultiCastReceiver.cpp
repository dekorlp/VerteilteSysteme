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

#include "MultiCastReceiver.h"

MultiCastReceiver::MultiCastReceiver(boost::asio::io_service& io_service,
        const boost::asio::ip::address& listen_address,
        const boost::asio::ip::address& multicast_address)
: socket_(io_service) {

    
    // Create the socket so that multiple may be bound to the same address.
    boost::asio::ip::udp::endpoint listen_endpoint(
            listen_address, multicast_port);
    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);
    cout << "GEH ST DU REIN? :)"<<endl;
    // Join the multicast group.
    socket_.set_option(
            boost::asio::ip::multicast::join_group(multicast_address));
    
    cout << "Port adr:" << multicast_port << endl;
    cout << "lisen cast adr:" << listen_address.to_string() << endl;
    cout << "Multi cast adr:" << multicast_address.to_string() << endl;
    
    socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), sender_endpoint_,
            boost::bind(&MultiCastReceiver::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

std::string MultiCastReceiver::receive() {
    socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), sender_endpoint_,
            boost::bind(&MultiCastReceiver::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

    string message = data_;
    cout << "SENDERENDPOINT: "<< sender_endpoint_.address().to_string() << endl;
    cout << "MESSAGE MULTICAST RECV: \n\n" << message<<"\n" << endl;
    cout << "MESSAGE MULTICAST DATA: \n\n" << endl;
    cout.write( data_,max_length);
    cout <<"\n" << endl;
    return message;
}

void MultiCastReceiver::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd) {

    cout << "IN HANDLE RECEIVE FROM " << endl;
    if (!error) {
        cout << "IN HANDLE RECEIVE FROM != ERROR" << endl;
        std::cout.write(data_, bytes_recvd);
        std::cout << std::endl;
        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&MultiCastReceiver::handle_receive_from, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}