#include "scanner.hpp"
#include <filesystem>

using namespace std;
namespace fs = filesystem;

Scanner::Scanner(string path) {
		if (!fs::exists(path)) throw invalid_argument("Path does not exist");
        this->dir_it = fs::directory_iterator(path);
        this->path = path; 
        // TODO: check for directory permissions
    }
