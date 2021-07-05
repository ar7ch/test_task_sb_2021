#ifndef THREATSCANREPORT_HPP
#define THREATSCANREPORT_HPP

#include "scanreport.hpp"
#include <chrono>
#include <sstream>
#include <array>

typedef int threat_type;
using namespace std;

class ThreatScanReport : ScanReport {
       public:
       struct threat_status {
            inline static const int CLEAN = 0; 
            inline static const int ERROR = 1; 
            inline static const int JS_THREAT = 2;
            inline static const int UNIX_THREAT = 3;
            inline static const int MACOS_THREAT = 4;
        };
        ThreatScanReport();
        void add_threat(threat_type);
   		void start_time_meas();
		void stop_time_meas();
        stringstream get_report();

        private:
        std::array<int,5> threats;
		std::chrono::time_point<std::chrono::steady_clock> time_begin, time_end;
		std::chrono::duration<double, std::chrono::microseconds::period> time_delta;
};

#endif
