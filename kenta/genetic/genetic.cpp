#include "getetic.h"

#include <stdlib.h>
#include <time.h>

GeneticAlgorithmforReversi::GeneticAlgorithmforReversi()
{
  srand(time(NULL));
  initChildren();
}

void initChildren()
{
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 19; j++)
    {
      children[i][j] = (rand() % 240) - 120;
    }
  }
}

void initNumberOfWins()
{
  for(int i = 0; i < 10; i++)
  {
    numberOfWins[i] = 0;
  }
}

void sortNumberOfWins()
{
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 9; j++)
    {
      if(numberOfWins[j] < numberOfWins[j + 1])
      {
        int swap = numberOfWins[j];
	numberOfWins[j] = numberOfWins[j + 1];
	numberOfWins[j + 1] = swap;
      }
    }
  }
}

GeneticAlgorithmforReversi::evaluate()
{
  
}

GeneticAlgorithmforReversi::choiceParent()
{
}

GeneticAlgorithmforReversi::crossParent()
{

}

GeneticAlgorithmforReversi::mutation()
{

}

