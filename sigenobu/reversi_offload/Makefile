#make file 
all: ab raspi

ab:  main_ab.cpp Board.o socket.o client_routine.o Reversi_AI_ab.o
	g++ -O3 -o client_ab.out main_ab.cpp Board.o socket.o client_routine.o Reversi_AI_ab.o 

raspi: raspi_socket.cpp 
	g++ -O3 -o client_raspi.out raspi_socket.cpp 

Board.o: Board.cpp Reversi.h Board.h
	g++ -O3 -c Board.cpp 

socket.o: socket.cpp socket.h
	g++ -O3 -c socket.cpp 

client_routine.o: client_routine.cpp client_routine.h
	g++ -O3 -c client_routine.cpp 

Reversi_AI_ab.o: Reversi_AI_ab.cpp Reversi_AI.h Board.h
	g++ -O3 -c Reversi_AI_ab.cpp 

clean:
	rm -f *.o *.out
