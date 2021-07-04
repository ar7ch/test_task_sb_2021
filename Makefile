.PHONY: build clean
FLAGS = -std=c++17 -Wall -Wfatal-errors 

build : scan_util scan_server scan_client

scan_client : client.o 
	g++ client.o $(FLAGS) -o scan_client
	@ echo "scan_client built successfully"

scan_server : server.o scanner.o threatscanner.o scanreport.o threatscanreport.o
	g++ server.o scanner.o threatscanner.o scanreport.o threatscanreport.o -o scan_server
	@echo "scan_server built successfully"

scan_util : main.o scanner.o threatscanner.o scanreport.o threatscanreport.o
	g++ main.o scanner.o threatscanner.o scanreport.o threatscanreport.o $(FLAGS) -o scan_util
	@ echo "scan_util built successfully"

client.o : client.cpp
	g++ -c client.cpp $(FLAGS) -o client.o

server.o : server.cpp
	g++ -c server.cpp $(FLAGS) -o server.o

main.o : main.cpp
	g++ -c main.cpp $(FLAGS) -o main.o

scanner.o : scanner.cpp 
	g++ -c scanner.cpp $(FLAGS) -o scanner.o

threatscanner.o : threatscanner.cpp
	g++ -c threatscanner.cpp $(FLAGS) -o threatscanner.o

scanreport.o : scanreport.cpp
	g++ -c scanreport.cpp $(FLAGS) -o scanreport.o

threatscanreport.o : threatscanreport.cpp
	g++ -c threatscanreport.cpp $(FLAGS) -o threatscanreport.o

clean : 
	rm *.out *.o
