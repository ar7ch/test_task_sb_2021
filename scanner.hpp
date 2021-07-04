#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <filesystem>
using namespace std;
namespace fs = filesystem;

class Scanner {
    protected:
        fs::directory_iterator dir_it;
        string path;
	
	public:
    Scanner(string path);
};

#endif