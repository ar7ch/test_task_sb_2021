#include "scanner.hpp"
#include "threatscanreport.hpp"

#ifndef THREATSCANNER_HPP
#define THREATSCANNER_HPP

using namespace std;
class ThreatScanner : Scanner {
    private:
        struct threat_patterns {
            inline static const string JS_THREAT = "<script>evil_script()</script>";
            inline static const string UNIX_THREAT = "rm -rf ~/Documents";
            inline static const string MACOS_THREAT = "system(\"launchctl load /Library/LaunchAgents/com.malware.agent\")";
        };
    public:
		ThreatScanner(string path);
        ThreatScanReport scan_all();
        threat_type scan_file(const fs::directory_entry entry);
};

#endif
