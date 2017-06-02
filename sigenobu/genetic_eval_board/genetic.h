#ifndef GENETIC_H
#define GENETIC_H

class GeneticAlgorithmforReversi
{
public:
  GeneticAlgorithmforReversi();
  void getEvaluateFunctionOfParent(int* evalBoard);
  void getEvaluateFunctionOfChild(int index, int* evalBoard);
  void createChildren();
  void setNumberOfWins(int index, int wins);

private:
  int parent[2][20];
  int children[10][20];
  int numberOfWins[10];

  void choiceParent();
  void crossParent();
  void mutation();

  void initChildren();
  void initNumberOfWins();

};

#endif
