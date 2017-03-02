all : main.o MessengerClient

clean : 
	rm -rf Debug/*.o Debug/MessengerClient

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
        CC = g++ -pthread
endif
ifeq ($(UNAME_S),Darwin)
        CC = g++
endif

main.o : main.cpp
	$(CC) -g -c -I../SocketUtils  main.cpp -o Debug/main.o
	
ClientController.o : ClientController.cpp
	$(CC) -g -c -I../SocketUtils  ClientController.cpp -o Debug/ClientController.o
	
ConnectionToServerManager.o : ConnectionToServerManager.cpp
	$(CC) -g -c ConnectionToServerManager.cpp -o Debug/ConnectionToServerManager.o
	
ClientTerminalPrinter.o : ClientTerminalPrinter.cpp
	$(CC) -g -c ClientTerminalPrinter.cpp -o Debug/ClientTerminalPrinter.o
	
CommandUtils.o : CommandUtils.cpp
	$(CC) -g -c CommandUtils.cpp -o Debug/CommandUtils.o

MessengerClient: ClientController.o ConnectionToServerManager.o ClientTerminalPrinter.o CommandUtils.o main.o
	$(CC) Debug/ClientTerminalPrinter.o Debug/CommandUtils.o Debug/ConnectionToServerManager.o Debug/ClientController.o Debug/main.o -L../SocketUtils/Debug -lSocketUtils -o Debug/MessengerClient 