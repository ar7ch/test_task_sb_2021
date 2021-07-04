#include <iostream>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <ctime>
#include <ratio>

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
            inline static const int CLEAN = 0; 
            inline static const int ERROR = 1; 
            inline static const int JS_THREAT = 2;
            inline static const int UNIX_THREAT = 3;
            inline static const int MACOS_THREAT = 4;
        };
        
        ThreatScanReport() {
            threats.fill(0);
        }

        void add_threat(threat_type type) {
			files_scanned++;
			(this->threats[type])++;
        }

   		inline void start_time_meas() {
			this->time_begin = chrono::steady_clock::now();
		}

		inline void stop_time_meas() {
			this->time_end = chrono::steady_clock::now();
			this->time_delta = chrono::duration_cast<chrono::duration<double, chrono::milliseconds::period>>(time_end-time_begin);
		}

        void print_report() {
            cout << "====== Scan result ======" << endl;
            cout << "Processed files: " << this->files_scanned << endl;
            cout << "JS detects: " << this->threats[ThreatScanReport::threat_status::JS_THREAT] << endl;
            cout << "Unix detects: " << this->threats[ThreatScanReport::threat_status::UNIX_THREAT] << endl;
            cout << "macOS detects: " << this->threats[ThreatScanReport::threat_status::MACOS_THREAT] << endl;
            cout << "Errors: " << this->errors << endl;
            cout << "Execution time (mm:ss:ms): " << 
				(int)(this->time_delta.count()/60000) << ":" << 
				(int)(this->time_delta.count()/1000) << ":" <<
				(int)(this->time_delta.count())%1000 << endl; // ugly but seems optimal without using C++20 or cstdlib
			cout << "=========================" << endl;
        }

        private:
        array<int,5> threats;
		chrono::time_point<chrono::steady_clock> time_begin, time_end;
		chrono::duration<double, chrono::milliseconds::period> time_delta;
		string mm_ss_ms;
};

class Scanner {
    protected:
        fs::directory_iterator dir_it;
        string path;
	
	public:
    Scanner(string path) {
		if (!fs::exists(path)) throw invalid_argument("Path does not exist");
        this->dir_it = fs::directory_iterator(path);
        this->path = path; 
        // TODO: check for directory permissions
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

		ThreatScanner(string path) : Scanner(path) {

		}

        ThreatScanReport scan_all() {
            ThreatScanReport report;
			//  Assuming the only I/O-intense process is iterating through the files in the directory,
			// 	we can begin time measurement from here...
			report.start_time_meas();
            for (const fs::directory_entry & entry : this->dir_it) {
                // TODO overload += for ScanReport, return report from scan_file and sum it 
                threat_type typ = scan_file(entry);
                report.add_threat(typ);
            }
			// and end it here
			report.stop_time_meas();
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
                    if(line.find(ThreatScanner::threat_patterns::JS_THREAT) != string::npos) {
                        return ThreatScanReport::threat_status::JS_THREAT;
                    }
                    if(line.find(ThreatScanner::threat_patterns::UNIX_THREAT) != string::npos) {
                        return ThreatScanReport::threat_status::UNIX_THREAT;
                    }
                    if(line.find(ThreatScanner::threat_patterns::MACOS_THREAT) != string::npos) {
                        return ThreatScanReport::threat_status::MACOS_THREAT;
                    }
                }
            }
			return ThreatScanReport::threat_status::CLEAN;
        }
};

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
