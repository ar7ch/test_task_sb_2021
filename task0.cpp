#include <iostream>
#include <filesystem>
#include <fstream>


using namespace std;
namespace fs = std::filesystem;
typedef int threat_type;

class ScanReport {
    protected:
        int files_scanned;
        int errors;
    public:
    ScanReport() {
        this->files_scanned = 0;
        this->errors = 0;
    }
};

class ThreatScanReport : ScanReport {
       public:
       struct threat_status {
            inline static const int ERROR = 0; 
            inline static const int JS_THREAT = 1;
            inline static const int UNIX_THREAT = 2;
            inline static const int MACOS_THREAT = 3;
        };
        
        ThreatScanReport() {
            threats.fill(0);
        }

        void add_threat(threat_type type) {
            (this->threats[type])++;
        }
        
        void get_report() {
            cout << "===== Scan result =====" << endl;
            cout << "Processed files: " << this->files_scanned << endl;
            cout << "JS detects: " << this->threats[ThreatScanReport::threat_status::JS_THREAT] << endl;
            cout << "Unix detects: " << this->threats[ThreatScanReport::threat_status::UNIX_THREAT] << endl;
            cout << "macOS detects: " << this->threats[ThreatScanReport::threat_status::MACOS_THREAT] << endl;
            cout << "Errors: " << this->errors << endl;
            cout << "Execution time: " << this->exec_time << endl; // TODO implement exec time
        }

        private:
        array<int,4> threats;
        int exec_time = 0; // TODO replace with chrono::duration

        
};

class Scanner {
    protected:
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
        struct threat_patterns {
            inline static const string JS_THREAT = "<script>evil_script()</script>";
            inline static const string UNIX_THREAT = "rm -rf ~/Documents";
            inline static const string MACOS_THREAT = "system(\"launchctl load /Library/LaunchAgents/com.malware.agent\")";
        };
    public:
        ThreatScanReport scan_all() {
            ThreatScanReport report;
            for (const fs::directory_entry & entry : this->dir_it) {
                // TODO overload += for ScanReport, return report from scan_file and sum it 
                threat_type typ = scan_file(entry);
                report.add_threat(typ);
            }
            return report;
        }

        threat_type scan_file(const fs::directory_entry entry) {
            ifstream file(entry.path(), ifstream::in);
            if (!file.is_open()) {
                return ThreatScanReport::threat_status::ERROR;
            }
            string line; line.reserve(160);
            while (!file.eof()) {
                getline(file, line);
                // вообще говоря, об ошибке желательно сообщать исключением, но в рамках задания ошибки считаются частью отчета
                if (file.fail()) return ThreatScanReport::threat_status::ERROR;
                else {
                    if(line.find(ThreatScanner::threat_patterns::JS_THREAT)) {
                        return ThreatScanReport::threat_status::JS_THREAT;
                    }
                    if(line.find(ThreatScanner::threat_patterns::UNIX_THREAT)) {
                        return ThreatScanReport::threat_status::UNIX_THREAT;
                    }
                    if(line.find(ThreatScanner::threat_patterns::MACOS_THREAT)) {
                        return ThreatScanReport::threat_status::MACOS_THREAT;
                    }
                }
            }        
        }
};

int main(int argc, char ** argv) {
    return 0;
}
