#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

using namespace std;

class Client {
	
	public:
	Client(string socket_addr, size_t buf_size);
	~Client();
	void init_client();
	void connect_server();
	void send_server(char * message);
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
