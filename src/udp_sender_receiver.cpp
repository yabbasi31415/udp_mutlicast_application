#include "udp_sender_receiver.h"

int start_chat()
{
  try
  {
    // if (argc != 3)
    // {
    //   std::cerr << "Usage: receiver <listen_address> <multicast_address>\n";
    //   std::cerr << "  For IPv4, try:\n";
    //   std::cerr << "    receiver 0.0.0.0 239.255.0.1\n";
    //   std::cerr << "  For IPv6, try:\n";
    //   std::cerr << "    receiver 0::0 ff31::8000:1234\n";
    //   return 1;
    // }

    boost::asio::io_service io_service;

    sender s(io_service, boost::asio::ip::address::from_string("239.5.6.1")); //(argv[2]));
    receiver r(io_service,
        boost::asio::ip::address::from_string("0.0.0.0"), //(argv[1]),
        boost::asio::ip::address::from_string("239.5.6.1")); //(argv[2]));
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}