#make file 
all: debug

debug: debug_main.cpp no_comm_reversi.o Board.o Reversi_AI_ab.o
	g++ -O3 -o debug_main.out debug_main.cpp Board.o no_comm_reversi.o Reversi_AI_ab.o

no_comm_reversi.o: no_comm_reversi.cpp Reversi.h Board.h GameMaster.h no_comm_reversi.h
	g++ -O3 -c  no_comm_reversi.cpp 

Board.o: Board.cpp Reversi.h Board.h
	g++ -O3 -c Board.cpp 

Reversi_AI_ab.o: Reversi_AI_ab.cpp Reversi_AI.h Board.h
	g++ -O3 -c Reversi_AI_ab.cpp 

clean:
	rm -f server.o Board.o reversi.out
