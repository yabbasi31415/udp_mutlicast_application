//
// chat_message.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <lyra/lyra.hpp>
#include "udp_sender_receiver.h"

using namespace lyra;

bool show_help = false;

class SetMultiCastGroup
{
public:
	std::string listen_ip;
	std::string multicast_ip;
	std::string multicast_port;

public:
  void run_parser(int argc, const char** argv) {
      auto parser
		= help(show_help).description(
			"Command Line Arguments\n"
			"chat -l <listen_ip> -m <multicast_ip> -p <multicast_port>.")
		| opt(listen_ip, "name")
			  ["-l"]["--name"]("The name to use.")
		| opt(multicast_ip, "name")
			  ["-m"]["--multicast"]("The ip to use.")
		| opt(multicast_port, "name")
			  ["-p"]["--address"]("The address to use.");

    auto result = parser.parse({argc,argv});

    if (!result)
    {
      std::cerr << result.errorMessage() << "\n\n";
    }
    if (show_help or !result)
    {
      std::cout << parser << "\n";
    }

  }

  void print()
  {
    std::cout << listen_ip << " " << " " << multicast_ip << " " << multicast_port << std::endl;
  }
	
};

#endif 

