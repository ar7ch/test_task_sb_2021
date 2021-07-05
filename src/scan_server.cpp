#include <server.hpp>

int main(int argc, char ** argv) {
	Server server(SOCKET_PATH, MAX_QUEUE, SERVER_BUF_SIZE);
	server.setup_server();
	server.server_loop();
   	return 0;
}
