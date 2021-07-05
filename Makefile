.PHONY: all clean
GREEN = '\033[0;32m'
NOC = '\033[0m'

# project-specific settings
SOCKET_PATH ?= '"/tmp/scan_service.socket"'
SERVER_BUF_SIZE ?= 160
MAX_QUEUE ?= 5
CLIENT_BUF_SIZE ?= 300

#
INCL_DIR := include
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wfatal-errors -I\$(INCL_DIR) -DSOCKET_PATH=$(SOCKET_PATH) -DSERVER_BUF_SIZE=$(SERVER_BUF_SIZE) -DMAX_QUEUE=$(MAX_QUEUE) -DCLIENT_BUF_SIZE=$(CLIENT_BUF_SIZE)
CPPFLAGS := 

OBJ_CLIENT = $(OBJ_DIR)/client.o $(OBJ_DIR)/scan_client.o 
OBJ_SERVER = $(OBJ_DIR)/server.o $(OBJ_DIR)/scan_server.o
OBJ_UTIL = $(OBJ_DIR)/scan_util.o
BASE_OBJ = $(OBJ_DIR)/scanner.o $(OBJ_DIR)/threatscanner.o $(OBJ_DIR)/scanreport.o $(OBJ_DIR)/threatscanreport.o 

EXE_CLIENT := $(BIN_DIR)/scan_client
EXE_SERVER := $(BIN_DIR)/scan_server
EXE_UTIL   := $(BIN_DIR)/scan_util

all : $(EXE_CLIENT) $(EXE_SERVER) $(EXE_UTIL)

$(EXE_CLIENT) : $(BIN_DIR) $(OBJ_DIR) $(OBJ_CLIENT) 
	$(CXX) $(OBJ_CLIENT) $(CXXFLAGS) -o $(EXE_CLIENT) 
	@ echo $(GREEN)"$(EXE_CLIENT) built successfully"$(NOC)

$(EXE_SERVER) : $(BIN_DIR) $(OBJ_DIR) $(OBJ_SERVER) $(BASE_OBJ) $(EXE_DIR) $(OBJ_DIR)
	$(CXX) $(OBJ_SERVER) $(BASE_OBJ) $(CXXFLAGS) -o $(EXE_SERVER)
	@echo $(GREEN)"$(EXE_SERVER) built successfully"$(NOC)

$(EXE_UTIL) : $(BIN_DIR) $(OBJ_DIR) $(OBJ_UTIL) $(BASE_OBJECTS) $(EXE_DIR) $(OBJ_DIR)
	$(CXX) $(OBJ_UTIL) $(BASE_OBJ) $(CXXFLAGS) -o $(EXE_UTIL)
	@ echo $(GREEN)"$(EXE_UTIL) built successfully"$(NOC)

$(BIN_DIR) : 
	mkdir -p $@

$(OBJ_DIR) :
	mkdir -p $@

#$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
#	$(CXX) -c $(SRC_DIR)/%.o $(CXXFLAGS) -o $(OBJ_DIR)/%.o

$(OBJ_DIR)/scan_client.o : $(SRC_DIR)/scan_client.cpp
	$(CXX) -c $(SRC_DIR)/scan_client.cpp $(CXXFLAGS) -o $(OBJ_DIR)/scan_client.o

$(OBJ_DIR)/client.o : $(SRC_DIR)/client.cpp
	$(CXX) -c $(SRC_DIR)/client.cpp $(CXXFLAGS) -o $(OBJ_DIR)/client.o

$(OBJ_DIR)/scan_server.o : $(SRC_DIR)/scan_server.cpp
	$(CXX) -c $(SRC_DIR)/scan_server.cpp $(CXXFLAGS) -o $(OBJ_DIR)/scan_server.o	

$(OBJ_DIR)/server.o : $(SRC_DIR)/server.cpp
	$(CXX) -c $(SRC_DIR)/server.cpp $(CXXFLAGS) -o $(OBJ_DIR)/server.o

$(OBJ_DIR)/scan_util.o : $(SRC_DIR)/scan_util.cpp
	$(CXX) -c $(SRC_DIR)/scan_util.cpp $(CXXFLAGS) -o $(OBJ_DIR)/scan_util.o

$(OBJ_DIR)/scanner.o : $(SRC_DIR)/scanner.cpp 
	$(CXX) -c $(SRC_DIR)/scanner.cpp $(CXXFLAGS) -o $(OBJ_DIR)/scanner.o

$(OBJ_DIR)/threatscanner.o : $(SRC_DIR)/threatscanner.cpp
	$(CXX) -c $(SRC_DIR)/threatscanner.cpp $(CXXFLAGS) -o $(OBJ_DIR)/threatscanner.o

$(OBJ_DIR)/scanreport.o : $(SRC_DIR)/scanreport.cpp
	$(CXX) -c $(SRC_DIR)/scanreport.cpp $(CXXFLAGS) -o $(OBJ_DIR)/scanreport.o

$(OBJ_DIR)/threatscanreport.o : $(SRC_DIR)/threatscanreport.cpp
	$(CXX) -c $(SRC_DIR)/threatscanreport.cpp $(CXXFLAGS) -o $(OBJ_DIR)/threatscanreport.o

clean : 
	@ rm -rv $(OBJ_DIR) $(BIN_DIR)
