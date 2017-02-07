all : main.o MessengerServer

clean : 
	rm -rf Debug/*.o Debug/MessengerServer

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
        CC = g++ -pthread
endif
ifeq ($(UNAME_S),Darwin)
        CC = g++
endif

MessengerServer: main.o
	$(CC) Debug/main.o -L../SocketUtils/Debug -lSocketUtils -o Debug/MessengerServer 

main.o : main.cpp
	$(CC) -g -c -I../SocketUtils  main.cpp -o Debug/main.o
