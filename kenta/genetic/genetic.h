#ifndef GENETIC_H
#define GENETIC_H

class GeneticAlgorithmforReversi
{
  int parent[5][19];
  int children[10][19];
  int numberOfWins[10];

  GeneticAlgorithmforReversi();
  void initChildren();
  void initNumberOfWins();
  void evaluate();
  void choiceParent();
  void crossParent();
  void mutation();
};

#endif
