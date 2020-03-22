#include <iostream>
#include <lyra/lyra.hpp>

int main(int argc, const char** argv)
{
	using namespace lyra;
	bool show_help = false;
	struct Config
	{
		std::string listen_ip;
		std::string multicast_ip;
		std::string multicast_port;
	} config;
	auto parser
		= help(show_help).description(
			"Command Line Arguments\n"
			"chat -l <listen_ip> -m <multicast_ip> -p <multicast_port>.")
		| opt(config.listen_ip, "name")
			  ["-l"]["--name"]("The name to use.")
		| opt(config.multicast_ip, "name")
			  ["-m"]["--multicast"]("The ip to use.")
		| opt(config.multicast_port, "name")
			  ["-p"]["--address"]("The address to use.");

	auto result = parser.parse({ argc, argv });

	if (!result)
	{
		std::cerr << result.errorMessage() << "\n\n";
	}
	if (show_help or !result)
	{
		std::cout << parser << "\n";
	}

	std::cout << config.listen_ip << " " << " " << config.multicast_ip << " " << config.multicast_port << std::endl;

	return 0;
}
