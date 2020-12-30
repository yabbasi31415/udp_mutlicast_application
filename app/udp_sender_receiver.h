#ifndef UDP_SENDER_RECEIVER_H
#define UDP_SENDER_RECEIVER_H

#include <boost/asio.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/bind/bind.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
using namespace boost::asio;

const short multicast_port = 30001;

class sender {
public:
  sender(boost::asio::io_service &io_service,
         const boost::asio::ip::address &multicast_address)
      : endpoint_(multicast_address, multicast_port),
        socket_(io_service, endpoint_.protocol()),
        stream_(io_service, STDIN_FILENO), timer_(io_service) {
    std::ostringstream os;

    std::string str_in;

    std::cout << "UDP send/receive started " << endpoint_ << "\n";

    async_read_until(stream_, b, '\n', read_handler);
  }

  std::function<void(boost::system::error_code, size_t)> read_handler =
      [&](boost::system::error_code ec, size_t len) {
        if (ec) {
          std::cerr << "exit with " << ec.message() << std::endl;
        } else {

          std::istream is(&b);
          std::getline(is, message_);

          socket_.async_send_to(boost::asio::buffer(message_), endpoint_,
                                boost::bind(&sender::handle_send_to, this,
                                            boost::asio::placeholders::error));
        }
      };

  void handle_send_to(const boost::system::error_code &error) {
    if (!error) {
      async_read_until(stream_, b, '\n', read_handler);
    }
  }

private:
  boost::asio::ip::udp::endpoint endpoint_;
  boost::asio::ip::udp::socket socket_;
  boost::asio::deadline_timer timer_;
  boost::asio::streambuf b;
  posix::stream_descriptor stream_;
  std::string message_;
};

class receiver {
  using udp_cb_t = std::function<void(std::string)>;
public:
  receiver(boost::asio::io_service &io_service,
           const boost::asio::ip::address &listen_address,
           const boost::asio::ip::address &multicast_address)
      : socket_(io_service) {
    // Create the socket so that multiple may be bound to the same address.
    boost::asio::ip::udp::endpoint listen_endpoint(listen_address,
                                                   multicast_port);
    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);

    // Join the multicast group.
    socket_.set_option(
        boost::asio::ip::multicast::join_group(multicast_address));

    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        boost::bind(&receiver::handle_receive_from, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }

  void handle_receive_from(const boost::system::error_code &error,
                           size_t bytes_recvd) {
    if (!error) {
      std::cout << "[ " << sender_endpoint_.address() << " "
                << sender_endpoint_.port() << "] ";
      std::cout.write(data_, bytes_recvd);
      std::cout << std::endl;

      _rx_cb(std::string(data_));
      // memset(data_,'\0',bytes_recvd);

      socket_.async_receive_from(
          boost::asio::buffer(data_, max_length), sender_endpoint_,
          boost::bind(&receiver::handle_receive_from, this,
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
    }
  }

  void bind_reception_callback(udp_cb_t cb)
  {
    _rx_cb = cb;
  }

private:
  boost::asio::ip::udp::socket socket_;
  boost::asio::ip::udp::endpoint sender_endpoint_;
  enum { max_length = 1024 };
  char data_[max_length];  
  udp_cb_t _rx_cb;
};

#endif
#endif