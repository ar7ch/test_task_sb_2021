#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class Scanner {
    private:
        fs::directory_iterator dir_it;
        string path;

    Scanner(string path) {
        this->dir_it = fs::directory_iterator(path);
        this->path = path; 
    }

};

class ThreatScanner : Scanner {

    ThreatScanReport scan_all() {
        ThreatScanReport report = new Report();
        for (const auto & entry : this->dir_it) {
            char typ = scan_file(entry);
            report.fill_report(type)
        }
    }

};

class ScanReport {
    private:
        int files_scanned;
};

class ThreatScanReport : ScanReport {
};
