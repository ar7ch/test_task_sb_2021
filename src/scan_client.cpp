#include <iostream>
#include <filesystem>
#include <errno.h>
#include <client.hpp>

using namespace std;

int main(int argc, char ** argv) {
    if (argc != 2) { 
		cerr << "usage: " << argv[0] << " <path to directory>" << endl;
        return EXIT_FAILURE;
    }
    else {
        try {
			const string path(argv[1]);
			if (!filesystem::exists(path)) throw invalid_argument("Path does not exist");	
			Client client(SOCKET_PATH, CLIENT_BUF_SIZE);
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
