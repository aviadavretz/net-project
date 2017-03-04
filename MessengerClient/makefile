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
	
ConnectionToServerManager.o : ConnectionToServerManager.cpp
	$(CC) -g -c -I../SocketUtils ConnectionToServerManager.cpp -o Debug/ConnectionToServerManager.o
	
ClientTerminalPrinter.o : ClientTerminalPrinter.cpp
	$(CC) -g -c -I../SocketUtils ClientTerminalPrinter.cpp -o Debug/ClientTerminalPrinter.o
	
ServerRepliesListener.o : ServerRepliesListener.cpp
	$(CC) -g -c -I../SocketUtils  ServerRepliesListener.cpp -o Debug/ServerRepliesListener.o
	
ClientController.o : ClientController.cpp
	$(CC) -g -c -I../SocketUtils  ClientController.cpp -o Debug/ClientController.o
	
main.o : main.cpp
	$(CC) -g -c -I../SocketUtils  main.cpp -o Debug/main.o

MessengerClient: ConnectionToServerManager.o ClientTerminalPrinter.o ServerRepliesListener.o ClientController.o main.o
	$(CC) Debug/ClientTerminalPrinter.o Debug/ConnectionToServerManager.o Debug/ServerRepliesListener.o Debug/ClientController.o Debug/main.o -L../SocketUtils/Debug -lSocketUtils -o Debug/MessengerClient 