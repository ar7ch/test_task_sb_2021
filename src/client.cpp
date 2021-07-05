#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <client.hpp>

using namespace std;

Client::Client(string socket_addr, size_t buf_size) {
		this->socket_addr = socket_addr;
		this->buf_size = buf_size;
		this->buf = new char[buf_size];
}

Client::~Client() {
		delete[] this->buf;
}

void Client::init_client() {
	this->inter_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(this->inter_fd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	// it is recommended to clear struct before using for portability
	memset(&(this->inter_addr), 0, sizeof(struct sockaddr_un));
	this->inter_addr.sun_family = AF_UNIX;
	strncpy(this->inter_addr.sun_path, this->socket_addr.c_str(), sizeof(this->inter_addr.sun_path)-1);
}

void Client::connect_server() {
	socklen_t struct_len = strlen(this->inter_addr.sun_path) + sizeof(this->inter_addr.sun_family);
	if (connect(this->inter_fd, (struct sockaddr *) &(this->inter_addr), struct_len) == -1){
		perror("connect");
		exit(EXIT_FAILURE);
	}
	cerr << "CLIENT: Connected to server" << endl;

}
	
void Client::send_server(char * message) {
	size_t bytes_sent;
	if ((bytes_sent = send(this->inter_fd, message, strlen(message), 0)) < 0) {
		perror("send");
		exit(EXIT_FAILURE);
	}
	cerr << "CLIENT: Successfully sent " << bytes_sent << " bytes" << endl;
}

void Client::recv_server() {
	memset(buf, '\0', buf_size);
	size_t bytes_recv;
	if ((bytes_recv=recv(this->inter_fd, buf, buf_size, 0)) < 0) {
		perror("recv");
		exit(EXIT_FAILURE);
	}
	cerr << "CLIENT: Successfully recieved " << bytes_recv << " bytes" << endl;
}
	
string Client::buf2str() {
	return string(this->buf);
}

void Client::disconnect() {
	close(this->inter_fd);
}
