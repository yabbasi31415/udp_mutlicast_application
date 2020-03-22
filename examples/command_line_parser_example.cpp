#include "parser.h"

int main(int argc, const char** argv)
{
	SetMultiCastGroup _udp;

	_udp.run_parser(argc, argv);
	// _udp.print();

	start_chat(_udp.listen_ip, _udp.multicast_ip, _udp.multicast_port);

	return 0;
}
