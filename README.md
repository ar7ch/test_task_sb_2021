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

### 3. От автора
Здравствуйте! <br><br>
    Перед тем, как Вы будете проверять мою работу, хотелось бы немного рассказать, чем я руководствовался, выполняя тестовое задание. <br><br>
    Архитектурно проект получился с минимальными различиями между простой и усложненной версиями, не считая межпроцессного взаимодействия клиента и сервера. Будучи больше "сишником", но выполняя задание под С++, я старался писать как можно более объектно-ориентированно. Межпроцессное взаимодействие происходит через Unix Domain Sockets, файл сокета по умолчанию лежит в `/tmp`. Говоря про сокеты, я попытался максимально обернуть взаимодействие с ними в классы Server и Client. <br><br>Весь код задумывался универсальным, чтобы мог использоваться как можно более широко, для "общего случая". Получилось это не везде.<br><br>
    Многие решения далеко не оптимальны: задание пришлось выполнять прямо в середине сессии, поэтому пришлось ужиматься в сроки, не все реализовано так, как я задумывал изначально. Некоторые пояснения на этот счет даны в исходном коде. Комментариев в коде мало, документации к функциям нет. Это связано с временными ограничениями, а также потому что код получился, на мой взгляд, легкочитаемый и простой. Комментарии и прочие пояснения на английском.<br><br>
    Структура проекта стандартная: директории `src`, `include`, `bin`, `obj`. Последние два появляются после сборки (на всякий случай приложу бинарники в архив на степике). В `test` лежат образцы подозрительных файлов: файлы только с подозрительным содержанием, они же, но среди других строк. Для проверки ошибок доступа у одного файла (a.sus) владелец root и права 711. Makefile, хоть и выполняет свою работу, из-за недостатка времени и того, что я долго не работал с make, написан недостаточно хорошо. Дополнительные сведения указаны в первых двух параграфах. <br>
<br>
    С наилучшими пожеланиями,<br>
<br>
    Артём.
