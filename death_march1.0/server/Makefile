#make file 
server: Board.o server.o
	g++ -O3 -o server.out Board.o server.o -fpermissive

server.o: server.cpp Reversi.h Board.h GameMaster.h
	g++ -c  server.cpp -fpermissive

Board.o: Board.cpp Reversi.h Board.h
	g++ -c Board.cpp -fpermissive

all: Board.cpp Board.h Reversi.h server.cpp  GameMaster.h
	g++ -O3  -o reversi.out  Board.cpp server.cpp  -fpermissive

clean:
	rm -f server.o Board.o reversi.out
