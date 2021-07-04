.PHONY: build clean
FLAGS = -std=c++17 -Wall -Wfatal-errors 

build : scan_util

scan_util : main.o scanner.o threatscanner.o scanreport.o threatscanreport.o
	g++ main.o scanner.o threatscanner.o scanreport.o threatscanreport.o $(FLAGS) -o scan_util
	@ echo "built successfully"

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
