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

ServerTerminalPrinter.o : ServerTerminalPrinter.cpp
	$(CC) -g -c ServerTerminalPrinter.cpp -o Debug/ServerTerminalPrinter.o

main.o : main.cpp
	$(CC) -g -c -I../SocketUtils  main.cpp -o Debug/main.o
	
MessengerServer: User.o Session.o ChatRoom.o ServerTerminalPrinter.o main.o
	$(CC) Debug/User.o Debug/Session.o Debug/ChatRoom.o Debug/ServerTerminalPrinter.o Debug/main.o -L../SocketUtils/Debug -lSocketUtils -o Debug/MessengerServer 
