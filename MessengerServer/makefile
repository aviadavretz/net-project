all : MessengerServer

clean : 
	rm -rf Debug/*.o Debug/MessengerServer

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
        CC = g++ -pthread
endif
ifeq ($(UNAME_S),Darwin)
        CC = g++
endif

User.o : User.cpp
	$(CC) -g -c User.cpp -o Debug/User.o

Session.o : Session.cpp
	$(CC) -g -c Session.cpp -o Debug/Session.o
	
ChatRoom.o : ChatRoom.cpp
	$(CC) -g -c ChatRoom.cpp -o Debug/ChatRoom.o
	
UserCredentialsManager.o : UserCredentialsManager.cpp
	$(CC) -g -c UserCredentialsManager.cpp -o Debug/UserCredentialsManager.o
	
ServerPeersAcceptor.o : ServerPeersAcceptor.cpp
	$(CC) -g -c -I../SocketUtils  ServerPeersAcceptor.cpp -o Debug/ServerPeersAcceptor.o
	
ServerPeersListener.o : ServerPeersListener.cpp
	$(CC) -g -c -I../SocketUtils  ServerPeersListener.cpp -o Debug/ServerPeersListener.o
	
ServerController.o : ServerController.cpp
	$(CC) -g -c -I../SocketUtils  ServerController.cpp -o Debug/ServerController.o
	
ServerTerminalPrinter.o : ServerTerminalPrinter.cpp
	$(CC) -g -c ServerTerminalPrinter.cpp -o Debug/ServerTerminalPrinter.o

main.o : main.cpp
	$(CC) -g -c -I../SocketUtils main.cpp -o Debug/main.o
	
MessengerServer: User.o Session.o ChatRoom.o UserCredentialsManager.o ServerPeersAcceptor.o ServerPeersListener.o ServerController.o ServerTerminalPrinter.o main.o
	$(CC) Debug/User.o Debug/Session.o Debug/ChatRoom.o Debug/ServerTerminalPrinter.o Debug/UserCredentialsManager.o Debug/ServerPeersAcceptor.o Debug/ServerPeersListener.o Debug/ServerController.o Debug/main.o -L../SocketUtils/Debug -lSocketUtils -o Debug/MessengerServer 
