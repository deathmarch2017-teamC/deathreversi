#make file 
server: Board.o GLserver.o
	g++ -O3 -o reversi.out libglut.so libGLU.so.1 libGL.so.1 Board.o GLserver.o -fpermissive

GLserver.o: GLserver.cpp Reversi.h Board.h GameMaster.h
	g++ -c  libglut.so libGLU.so.1 libGL.so.1  GLserver.cpp -fpermissive

Board.o: Board.cpp Reversi.h Board.h
	g++ -c Board.cpp -fpermissive

all: Board.cpp Board.h Reversi.h server_tcp.cpp  GameMaster.h
	g++ -O3  -o reversi.out  Board.cpp server_tcp.cpp  -fpermissive


clean:
	rm -f server_tcp.o Board.o reversi.out
