#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#ifndef SOCKET_ADDR
#define SOCKET_ADDR "/tmp/scan_service.socket"
#endif

#ifndef CLIENT_BUF_SIZE
	#define CLIENT_BUF_SIZE 500
#endif

using namespace std;

class Client {
	
	public:
	Client(string, size_t);
	~Client();
	void init_client();
	void connect_server();
	void send_server(char *);
	void recv_server();	
	string buf2str();
	void disconnect();

	private:
	int inter_fd;
	struct sockaddr_un inter_addr;
	string socket_addr;
	char * buf;
	size_t buf_size;
		
};

#endif
