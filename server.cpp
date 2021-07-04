#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "threatscanner.hpp"
#include "threatscanreport.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

using namespace std;
class Server {
	public:
	Server(){//char * socket_addr, max_queue) {
		// TODO implement me
	}
	
	void setup_server() {
		this->listen_sfd = socket(AF_UNIX, SOCK_STREAM, 0);
		if (this->listen_sfd == -1) {
			perror("socket");
			exit(EXIT_FAILURE);
		}
		this->listen_addr.sun_family = AF_UNIX;
		//memset((void *)(&this->listen_addr), 0, sizeof(struct sockaddr_un));
		strcpy(this->listen_addr.sun_path, this->socket_addr); //FIXME unsafe
		size_t struct_len = sizeof(this->listen_addr.sun_family) + strlen(this->socket_addr);
		unlink(listen_addr.sun_path);
		int status = bind(this->listen_sfd, (const struct sockaddr *) &(this->listen_addr), struct_len);
		if(status == -1) {
			perror("bind");
			exit(EXIT_FAILURE);
		}
	}

	void server_loop(){
		char buf[160];
		while(1)
		{
			memset((void *)buf, '\0', 160);
			listen(this->listen_sfd, this->max_queue);
			socklen_t inter_addr_len = sizeof(struct sockaddr_un);
			this->inter_fd = accept(listen_sfd, (struct sockaddr *) &(this->inter_addr), &(inter_addr_len));
			cout << "accepted incoming connection" << endl;
			ssize_t recv_len = recv(this->inter_fd, buf, 160, 0);
			if (recv_len < 0) {
				perror("recv");
				exit(EXIT_FAILURE);
			}
			/*
			ThreatScanner ts(path);
            ThreatScanReport tr = ts.scan_all();
			tr.print_report();*/
    
			cout << string(buf);
			send(this->inter_fd, buf, strlen(buf), 0);			
			close(this->inter_fd);
			cout << "connection closed" << endl;
		}
	}
	private:
	int max_queue = 2;	
	int listen_sfd; // socket listening for incoming connect
	int inter_fd; // socket for interaction with connected client
	struct sockaddr_un listen_addr;
	struct sockaddr_un inter_addr;
	char socket_addr[108] = "/home/artem/task1/scan_service.socket";  
};
using namespace std;

int main(int argc, char ** argv) {
	Server server;
	server.setup_server();
	server.server_loop();
   	return 0;
}