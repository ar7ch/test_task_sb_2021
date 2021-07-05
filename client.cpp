#include <iostream>
#include <cstdio>
#include <filesystem>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>


using namespace std;

class Client {
	
	public:
	void init_client(){
		this->inter_fd = socket(AF_UNIX, SOCK_STREAM, 0);
		if(this->inter_fd == -1) {
			perror("socket");
			exit(EXIT_FAILURE);
		}
		// it is recommended to clear struct before using for portability
		memset(&(this->inter_addr), 0, sizeof(struct sockaddr_un));
		this->inter_addr.sun_family = AF_UNIX;
		strncpy(this->inter_addr.sun_path, this->socket_addr, sizeof(this->inter_addr.sun_path)-1);
	}
	void connect_server() {
		socklen_t struct_len = strlen(this->inter_addr.sun_path) + sizeof(this->inter_addr.sun_family);
		if (connect(this->inter_fd, (struct sockaddr *) &(this->inter_addr), struct_len) == -1){
			perror("connect");
			exit(EXIT_FAILURE);
		}
		cerr << "CLIENT: Connected to server" << endl;

	}
	
	void send_server(char * message) {
		size_t bytes_sent;
		if ((bytes_sent = send(this->inter_fd, message, strlen(message), 0)) < 0) {
			perror("send");
			exit(EXIT_FAILURE);
		}
		cerr << "CLIENT: Successfully sent " << bytes_sent << " bytes" << endl;
	}

	void recv_server() {
		this->buf = new char[buf_size];
		memset(buf, '\0', buf_size);
		size_t bytes_recv;
		if ((bytes_recv=recv(this->inter_fd, buf, buf_size, 0)) < 0) {
			perror("recv");
			exit(EXIT_FAILURE);
		}
		cerr << "CLIENT: Successfully recieved " << bytes_recv << " bytes" << endl;
	}
	
	string buf2str() {
		return string(this->buf);
	}

	void disconnect() {
		close(this->inter_fd);
	}

	private:
	int inter_fd;
	struct sockaddr_un inter_addr;
	char socket_addr[160]="/home/artem/task1/scan_service.socket";
	char * buf;
	size_t buf_size = 500;
		
};

int main(int argc, char ** argv) {
    if (argc != 2) { 
		cerr << "usage: " << argv[0] << " <path to directory>" << endl;
        return EXIT_FAILURE;
    }
    else {
        try {
			const string path(argv[1]);
			if (!filesystem::exists(path)) throw invalid_argument("Path does not exist");	
			Client client;
			client.init_client();
			client.connect_server();
			client.send_server(argv[1]);
			client.recv_server();
			cout << client.buf2str() << endl;
			client.disconnect();
        }
        catch (const invalid_argument& ia) {
            cerr << "ERROR: " << ia.what() << endl; 
            return EXIT_FAILURE;
        }
    }
    return 0;
}
