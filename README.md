# Safeboard 2021 test task
## Threat scan applications
### 1. Overview
* <b>`scan_util`</b> - a simple program that scans given directory.
<br>Usage: `$ scan_util /path/to/dir`
* <b>`scan_server` and `scan_client`</b> - a client-server filesystem scanning software. <br>Usage:<br>I. Launch server: `$ scan_server 2> server.log &` (server log is sent via stderr)<br>II. Scan the desirable directory: `$ scan_client /path/to/dir 2> client.log` (client logs to stderr as well)<br> Relative paths are supported!<br>There is a test folder with example suspicious files in the project root.
### 2. Build
<b>Basic requirements:</b> a POSIX-compliant operating system, `g++` with C++17 support, GNU make. Developed and tested on Ubuntu Linux 20.04, macOS and other platforms support is not guaranteed.<br>
<br>
In the project root directory, run `make all` with desired arguments. Three binary files will be generated at `bin`. Available parameters <b>(only make sense for the client-server version)</b> and their default values (see Makefile):
* `SOCKET_PATH = "/tmp/scan_service.socket"` - path where Unix socket used by client-server to communicate is located.
* `SERVER_BUF_SIZE = 160` - server's buffer size used for receiving messages.
* `MAX_QUEUE = 5` - maximum quantity of server's queued connections.
* `CLIENT_BUF_SIZE = 300` - client's buffer size used for receiving messages.
