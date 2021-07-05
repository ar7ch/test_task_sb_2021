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

#define SOCKET_ADDR "/home/artem/task1/scan_service.socket"
#define SERVER_BUF_SIZE 160
#define MAX_QUEUE 5

using namespace std;
class Server {
	public:
	Server(string sock_addr, int max_queue, size_t buf_size) {
		this->socket_addr = sock_addr;
		this->max_queue = max_queue;
		this->buf_size = buf_size;
		this->buf = new char[this->buf_size];
	}

	~Server() {
		delete[] this->buf;
	}
	
	void setup_server() {
		this->listen_sfd = socket(AF_UNIX, SOCK_STREAM, 0);
		if (this->listen_sfd == -1) {
			perror("socket");
			exit(EXIT_FAILURE);
		}
		memset(&(this->listen_addr), 0, sizeof(struct sockaddr_un));
		this->listen_addr.sun_family = AF_UNIX;
		strncpy(this->listen_addr.sun_path, this->socket_addr.c_str(), sizeof(this->listen_addr.sun_path)-1);
		size_t struct_len = sizeof(this->listen_addr.sun_family) + strlen(this->listen_addr.sun_path);
		unlink(listen_addr.sun_path);
		int status = bind(this->listen_sfd, (const struct sockaddr *) &(this->listen_addr), struct_len);
		if(status == -1) {
			perror("bind");
			exit(EXIT_FAILURE);
		}
	}

	void server_loop(){
		while(1)
		{
			memset(this->buf, '\0', this->buf_size);
			listen(this->listen_sfd, this->max_queue);
			socklen_t inter_addr_len = sizeof(struct sockaddr_un);
			this->inter_fd = accept(listen_sfd, (struct sockaddr *) &(this->inter_addr), &(inter_addr_len));
			cerr << "SERVER: accepted incoming connection" << endl;
			ssize_t recv_len = recv(this->inter_fd, this->buf, this->buf_size, 0);
			if (recv_len < 0) {
				perror("recv");
				exit(EXIT_FAILURE);
			}
			
			ThreatScanner ts(this->buf);
            ThreatScanReport tr = ts.scan_all();
			string str = tr.get_report().str();
			const char * report_ptr = str.c_str();
			if (send(this->inter_fd, report_ptr, strlen(report_ptr), 0) < 0) {
				perror("send");
				exit(EXIT_FAILURE);
			};	

			close(this->inter_fd);
			cerr << "SERVER: connection closed" << endl;
		}
	}
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

int main(int argc, char ** argv) {
	Server server(SOCKET_ADDR, MAX_QUEUE, SERVER_BUF_SIZE);
	server.setup_server();
	server.server_loop();
   	return 0;
}
