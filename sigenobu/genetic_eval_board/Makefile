#make file 
all: eval_genetic

eval_genetic: no_comm_reversi.o Reversi_AI_ab.o genetic.o Board.o 
	g++ -O3 -o eval_genetic.out eval_genetic.cpp no_comm_reversi.o Reversi_AI_ab.o genetic.o Board.o

genetic.o: genetic.cpp genetic.h
	g++ -O3 -c genetic.cpp

no_comm_reversi.o: no_comm_reversi.cpp Reversi.h Board.h GameMaster.h no_comm_reversi.h
	g++ -O3 -c  no_comm_reversi.cpp 

Board.o: Board.cpp Reversi.h Board.h
	g++ -O3 -c Board.cpp 

Reversi_AI_ab.o: Reversi_AI_ab.cpp Reversi_AI.h Board.h
	g++ -O3 -c Reversi_AI_ab.cpp 

clean:
	rm -f server.o Board.o reversi.out
