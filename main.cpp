#include <iostream>
#include <cstdio>
#include "threatscanner.hpp"
#include "threatscanreport.hpp"

using namespace std;

int main(int argc, char ** argv) {
    if (argc != 2) { 
		cerr << "usage: " << argv[0] << " <path to directory>" << endl;
        return 1;
    }
    else {
        try {
			const string path(argv[1]);
            ThreatScanner ts(path);
            ThreatScanReport tr = ts.scan_all();
			tr.print_report();
        }
        catch (const invalid_argument& ia) {
            cerr << "ERROR: " << ia.what() << endl; 
            return 2;
        }
    }
    return 0;
}
