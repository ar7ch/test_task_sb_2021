#include <iostream>
#include <cstdio>
#include <threatscanner.hpp>
#include <threatscanreport.hpp>
#include <errno.h>

using namespace std;

int main(int argc, char ** argv) {
    if (argc != 2) { 
		cerr << "usage: " << argv[0] << " <path to directory>" << endl;
        return EXIT_FAILURE;
    }
    else {
        try {
			const string path(argv[1]);
            ThreatScanner ts(path);
            ThreatScanReport tr = ts.scan_all();
			cout << tr.get_report().str();
        }
        catch (const invalid_argument& ia) {
            cerr << "ERROR: " << ia.what() << endl; 
            return EXIT_FAILURE;
        }
    }
    return 0;
}
