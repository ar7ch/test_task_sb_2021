#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;
typedef int threat_type;

class Scanner {
    private:
        fs::directory_iterator dir_it;
        string path;

    Scanner(string path) {
        this->dir_it = fs::directory_iterator(path);
        this->path = path; 
        // TODO: check for directory existence and permissions
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

    char scan_file(fs::directory_entry entry) {
        basic_ifstream f = basic_ifstream(entry.path());
        // TODO check for errors
        f.open();
        // TODO implement linewise pattern search 
        f.close();
    }        

};

class ScanReport {
    private:
        int files_scanned;
        int errors;

    ScanReport() {
        this->files_scanned = 0;
        this->errors = 0;
    }
};

class ThreatScanReport : ScanReport {
    private:
        int threats[3];

    public:
        int JS_THREAT = 0;
        int UNIX_THREAT = 1;
        int MACOS_THREAT = 2;

    ThreatScanReport() {
        this->js_threats = 0;
        this->unix_threats = 0;
        this->macos_threats = 0;
    }

    void add_threat(threat_type type) {
        (this->threats[type])++;
    }

    void get_report() {
        cout << "===== Scan result =====" << endl;
        cout << "Processed files: " << this->files_scanned << endl;
        cout << "JS detects: " << this->threats[JS_THREAT] << endl;
        cout << "Unix detects: " << this->threats[UNIX_THREAT] << endl;
        cout << "macOS detects: " << this->threat[MACOS_THREAT] << endl;
        cout << "Errors: " << this->errors << endl;
        cout << "Execution time: " << this->exec_time << endl; // TODO implement exec time
    }
        
};
