#include "threatscanner.hpp"
#include "threatscanreport.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>

typedef int threat_type;
using namespace std;

ThreatScanReport::ThreatScanReport() {
	threats.fill(0);
}

void ThreatScanReport::add_threat(threat_type type) {
	files_scanned++;
	(this->threats[type])++;
}

void ThreatScanReport::start_time_meas() {
	this->time_begin = chrono::steady_clock::now();
}

void ThreatScanReport::stop_time_meas() {
	this->time_end = chrono::steady_clock::now();
	this->time_delta = chrono::duration_cast<chrono::duration<double, chrono::milliseconds::period>>(time_end-time_begin);
}

void ThreatScanReport::print_report() {
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
