#include "threatscanner.hpp"
#include "threatscanreport.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>
#include <sstream>

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
	this->time_delta = chrono::duration_cast<chrono::duration<double, chrono::microseconds::period>>(time_end-time_begin);
}

stringstream ThreatScanReport::get_report() {
	stringstream sstr;	
	sstr << "====== Scan result ======" << endl << "Processed files: " << this->files_scanned << endl << 
		"JS detects: " << this->threats[ThreatScanReport::threat_status::JS_THREAT] << endl <<
		"Unix detects: " << this->threats[ThreatScanReport::threat_status::UNIX_THREAT] << endl <<
		"macOS detects: " << this->threats[ThreatScanReport::threat_status::MACOS_THREAT] << endl << 
		"Errors: " << this->errors << endl <<
		"Execution time (ss:ms:us): " << setw(2) << setfill('0') <<
		(int)(this->time_delta.count()/1000000) << ":" << setw(2) << setfill('0') <<
		(int)(this->time_delta.count()/1000) << ":" << setw(2) << setfill('0') <<
		(int)(this->time_delta.count())%1000 << endl << // ugly but seems optimal without using C++20 or cstdlib
		"=========================" << endl;
	return sstr;
}
