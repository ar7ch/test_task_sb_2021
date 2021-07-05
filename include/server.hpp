#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>

#ifndef SOCKET_PATH
	#define SOCKET_PATH "/tmp/scan_service.socket"
#endif 

#ifndef SERVER_BUF_SIZE
	#define SERVER_BUF_SIZE 160
#endif

#ifndef MAX_QUEUE
	#define MAX_QUEUE 5
#endif

using namespace std;

class Server {

	public:
	Server(string sock_addr, int max_queue, size_t buf_size);
	~Server();
	void setup_server();
	void server_loop();
	private:
	int max_queue;	
	int listen_sfd; // socket listening for incoming connect
	int inter_fd; // socket for interaction with connected client
	struct sockaddr_un listen_addr;
	struct sockaddr_un inter_addr;
	char * buf;
	size_t buf_size;
	string socket_addr;
};

#endif
