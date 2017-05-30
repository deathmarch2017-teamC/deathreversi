#make file 
all: client

client: Board.o socket.o client_routine.o Reversi_AI_Random.o
	g++ -g -o client.out main_client.cpp Board.o socket.o client_routine.o Reversi_AI_Random.o 

minimax:  Board.o socket.o client_routine.o Reversi_AI_Minimax.o
	g++ -g -o client_minimax.out main_Minimax.cpp Board.o socket.o client_routine.o Reversi_AI_Minimax.o 

Board.o: Board.cpp Reversi.h Board.h
	g++ -c Board.cpp 

socket.o: socket.cpp socket.h
	g++ -c socket.cpp 

client_routine.o: client_routine.cpp client_routine.h
	g++ -c client_routine.cpp 

Reversi_AI_Random.o: Reversi_AI_Random.cpp Reversi_AI.h Board.h
	g++ -c Reversi_AI_Random.cpp 

Reversi_AI_Minimax.o: Reversi_AI_Minimax.cpp Reversi_AI.h Board.h
	g++ -c Reversi_AI_Minimax.cpp 

clean:
	rm -f *.o *.out
