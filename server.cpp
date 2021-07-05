#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "threatscanner.hpp"
#include "threatscanreport.hpp"
#include "server.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

using namespace std;

Server::Server(string sock_addr, int max_queue, size_t buf_size) {
	this->socket_addr = sock_addr;
	this->max_queue = max_queue;
	this->buf_size = buf_size;
	this->buf = new char[this->buf_size];
}

Server::~Server() {
	delete[] this->buf;
}
	
void Server::setup_server() {
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

void Server::server_loop() {
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
		/* there is a considerable overhead in sending the whole plaintext report via socket
		 * probably the most suitable solution is serializing threatscanreport instance and sending it
		 * however dealing with serializing, sending and deserializing binary data
		 * would require some hours of debugging and unfortunately i'm running out of time
		 */
		const char * report_ptr = str.c_str();
		if (send(this->inter_fd, report_ptr, strlen(report_ptr), 0) < 0) {
			perror("send");
			exit(EXIT_FAILURE);
		};	

		close(this->inter_fd);
		cerr << "SERVER: connection closed" << endl;
	}
}
