.PHONY: build clean
FLAGS = -std=c++17 -Wall -Wfatal-errors 
GREEN = '\033[0;32m'

BASE_OBJECTS = scanner.o threatscanner.o scanreport.o threatscanreport.o 

build : scan_util scan_server scan_client

scan_client : scan_client.o client.o 
	g++ client.o scan_client.o $(FLAGS) -o scan_client
	@ echo $(GREEN)"scan_client built successfully"

scan_server : scan_server.o server.o $(BASE_OBJECTS) 
	g++ scan_server.o server.o $(BASE_OBJECTS) -o scan_server
	@echo $(GREEN)"scan_server built successfully"

scan_util : main.o $(BASE_OBJECTS) 
	g++ main.o $(BASE_OBJECTS) $(FLAGS) -o scan_util
	@ echo $(GREEN)"scan_util built successfully"

scan_client.o : scan_client.cpp
	g++ -c scan_client.cpp $(FLAGS) -o scan_client.o

client.o : client.cpp
	g++ -c client.cpp $(FLAGS) -o client.o

scan_server.o : scan_server.cpp
	g++ -c scan_server.cpp $(FLAGS) -o scan_server.o	

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
