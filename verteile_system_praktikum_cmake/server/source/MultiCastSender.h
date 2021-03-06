//
// sender.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <sstream>
#include <string>
#include <mutex>
#include <vector>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "../gen-cpp/ShopRequest.h"

using namespace std;
const short multicast_port = 30001;
const int max_message_count = 10;

class MultiCastSender
{
public:
  MultiCastSender(boost::asio::io_service& io_service,
      const boost::asio::ip::address& multicast_address,
          vector<ProductAnswer>& orderList,
          mutex &mutex);

  string encodeMessage(ProductAnswer);
  
  void send_routine(const boost::system::error_code& error);
  void handle_send_to(const boost::system::error_code& error);

  void handle_timeout(const boost::system::error_code& error);

private:
  boost::asio::ip::udp::endpoint endpoint_;
  boost::asio::ip::udp::socket socket_;
  boost::asio::deadline_timer timer_;
  int message_count_;
  std::string message_;
  vector<ProductAnswer> *orderList = 0;
  mutex *m = 0;
};
