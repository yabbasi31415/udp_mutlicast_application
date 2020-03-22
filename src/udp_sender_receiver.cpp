#include "udp_sender_receiver.h"

int start_chat(std::string listen_ip, std::string multicast_ip, std::string multicast_port)
{
  try
  {
    boost::asio::io_service io_service;

    // sender s(io_service, boost::asio::ip::address::from_string("239.5.6.1")); 
    sender s(io_service, boost::asio::ip::address::from_string(multicast_ip)); 
    receiver r(io_service,
        boost::asio::ip::address::from_string("0.0.0.0"),
        // boost::asio::ip::address::from_string(listen_ip),
        // boost::asio::ip::address::from_string("239.5.6.1"));
        boost::asio::ip::address::from_string(multicast_ip));
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}