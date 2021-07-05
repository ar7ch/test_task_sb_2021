#include <server.hpp>

#ifndef SOCKET_PATH
	#define SOCKET_PATH "/tmp/scan_service.socket"
#endif

#ifndef MAX_QUEUE
	#define MAX_QUEUE 5
#endif

#ifndef SERVER_BUF_SIZE
	#define SERVER_BUF_SIZE 160
#endif

int main(int argc, char ** argv) {
	Server server(SOCKET_PATH, MAX_QUEUE, SERVER_BUF_SIZE);
	server.setup_server();
	server.server_loop();
   	return 0;
}
