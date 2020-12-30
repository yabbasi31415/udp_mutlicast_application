#include "udp_sender_receiver.h"

void on_udp_reception(std::string message)
{}

int main(int argc, char *argv[]) {
  boost::asio::io_service io_service;  

  sender s(io_service, boost::asio::ip::address::from_string("239.0.0.0"));
  receiver r(io_service, boost::asio::ip::address::from_string("0.0.0.0"),
             boost::asio::ip::address::from_string("239.0.0.0"));
             
  r.bind_reception_callback(std::bind(on_udp_reception, std::placeholders::_1));

  io_service.run();

}
