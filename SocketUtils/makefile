all : libSocketUtils.a

clean : 
	rm -rf Debug/*.o Debug/libSocketUtils.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
        CC = g++ -pthread  
endif
ifeq ($(UNAME_S),Darwin)
	CC = g++ 
endif

MThread.o : MThread.cpp 
	$(CC) -g -c MThread.cpp -o Debug/MThread.o

UDPSocket.o : UDPSocket.cpp 
	$(CC) -g -c UDPSocket.cpp -o Debug/UDPSocket.o

TCPSocket.o : TCPSocket.cpp
	$(CC) -g -c TCPSocket.cpp -o Debug/TCPSocket.o
	
MTCPListener.o : MTCPListener.cpp
	$(CC) -g -c MTCPListener.cpp -o Debug/MTCPListener.o
	
CommandUtils.o : CommandUtils.cpp
	$(CC) -g -c CommandUtils.cpp -o Debug/CommandUtils.o

libSocketUtils.a : MThread.o UDPSocket.o TCPSocket.o MTCPListener.o CommandUtils.o
	ar -crv Debug/libSocketUtils.a Debug/MThread.o Debug/UDPSocket.o Debug/TCPSocket.o Debug/MTCPListener.o Debug/CommandUtils.o