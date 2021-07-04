#include "threatscanner.hpp"
#include "threatscanreport.hpp"
#include <filesystem>
#include <string>
#include <fstream>

using namespace std;
namespace fs = filesystem;


ThreatScanner::ThreatScanner(string path) : Scanner(path) {

}

ThreatScanReport ThreatScanner::scan_all() {
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

threat_type ThreatScanner::scan_file(const fs::directory_entry entry) {
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
