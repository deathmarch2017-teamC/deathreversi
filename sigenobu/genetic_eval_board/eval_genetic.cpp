#include "genetic.h"
#include "no_comm_reversi.h"
#define MAX_CHILDREN 10
#define MAX_GENERATION 500

int main() {
  int judge;
  int e_board[2][BOARD_SIZE*BOARD_SIZE];
  int p_board[BOARD_SIZE*BOARD_SIZE];
  GeneticAlgorithmforReversi genreversi;
  int wincount[10];
  int generation_count = 1;

  while(1){
    for (int i = 0; i < MAX_CHILDREN-1; i++){
      for (int j = i+1; j < MAX_CHILDREN; j++){
	genreversi.getEvaluateFunctionOfChild(i,e_board[0]);
	genreversi.getEvaluateFunctionOfChild(j,e_board[1]);
	judge = abvsab(e_board[0], e_board[1]);
	if(judge > 0) wincount[i]++;
	else if(judge < 0) wincount[j]++;

	judge = abvsab(e_board[1], e_board[0]);
	if(judge > 0) wincount[j]++;
	else if(judge < 0) wincount[i]++;

      }
    }
    for(int i = 0; i < MAX_CHILDREN; i++){
      genreversi.setNumberOfWins(i, wincount[i]);
    }

    genreversi.createChildren();
    genreversi.getEvaluateFunctionOfParent(p_board);
    
    std::cout << "Genelation " << generation_count << std::endl;

    std::cout << "    a b c d e f g h i j k l " << std::endl;
    for(int y=1; y<=BOARD_SIZE; y++)
      {
	if(y<10){
	  std::cout << " 0" <<dec<< y;
	}
	else{
	  std::cout <<" "<<dec<<y;
	}
	for(int x=1; x<=BOARD_SIZE; x++)
	  {
	    std::cout << " " << p_board[x+y*BOARD_SIZE];
	  }
	std::cout << std::endl;
      }
    std::cout << std::endl << std::endl;
    if(generation_count > MAX_GENERATION) break;
  }

}
