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
    private:
        static struct threat_patterns {
            string JS_THREAT = "<script>evil_script()</script>";
            string UNIX_THREAT = "rm -rf ~/Documents";
            string MACOS_THREAT = "system(\"launchctl load /Library/LaunchAgents/com.malware.agent\")";
        }
    public:
        ThreatScanReport scan_all() {
            ThreatScanReport report;
            for (const auto & entry : this->dir_it) {
                // TODO overload += for ScanReport, return report from scan_file and sum it 
                threat_type typ = scan_file(entry);
                report.add_threat(typ);
            }
            return report;
        }

        threat_type scan_file(fs::directory_entry entry) {
            ifstream file(entry.path());
            if (!file.is_open()) {
                return ThreatScanReport.ERROR;
            }
            string line; line.reserve(160);
            while(!file.eof()) {
                getline(file, &line);
                if(file.fail()) return threat_type.ERROR;
                if(file.find(ThreatScanner.threat_patterns.JS_THREAT)) {
                    return ThreatScanReport.threat_status.JS_THREAT;
                }
                if(file.find(ThreatScanner.threat_patterns.UNIX_THREAT)) {
                    return ThreatScanReport.threat_status.UNIX_THREAT;
                }
                if(file.find(ThreatScanner.threat_patterns.MACOS_THREAT)) {
                    return ThreatScanReport.threat_status.MACOS_THREAT;
                }
            }        
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
        array<int> threats;
        int exec_time = 0; // TODO replace with chrono::duration

    public:
        static struct threat_status {
            int ERROR = 0 : 1; 
            int JS_THREAT = 1 : 2;
            int UNIX_THREAT = 2 : 2;
            int MACOS_THREAT = 3 : 2;
        }

    ThreatScanReport() {
        threats.fill(0);
   }

    void add_threat(threat_type type) {
        (this->threats[type])++;
    }
    
    void fill_report
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
