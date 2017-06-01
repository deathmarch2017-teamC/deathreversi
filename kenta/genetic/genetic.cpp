/*! @file
 @brief $B%3%s%9%H%i%/%?(B
 @author $B?70f(B
 @date 2017.6.2
*/

#include "getetic.h"

#include <stdlib.h>
#include <time.h>

/*! @brief $B%3%s%9%H%i%/%?(B
*/
GeneticAlgorithmforReversi::GeneticAlgorithmforReversi()
{
  srand(time(NULL));
  initChildren();
  initNumberOfWins();
}

/*! @brief $B?F$NI>2A%\!<%I$rJV$9(B
 @param[in] index $B?F$N%$%s%G%C%/%9(B(0$B$+(B1)
 @param[out] evalBoard $BI>2A%\!<%I(B(int$B7?(B1$B<!85G[Ns(B)
*/
void GeneticAlgorithmforReversi::getEvaluateFunctionOfParent(int* evalBoard)
{
  for(i = 0; i < 6; i++)
  {
    for(j = i; j < 6; j++)
    {
      evalBoard[    i    * 12 +     j   ] = parent[0][j];
      evalBoard[    i    * 12 + (11 - j)] = parent[0][j];
      evalBoard[    j    * 12 +     i   ] = parent[0][j];
      evalBoard[    j    * 12 + (11 - i)] = parent[0][j];
      evalBoard[(11 - i) * 12 +     j   ] = parent[0][j];
      evalBoard[(11 - i) * 12 + (11 - j)] = parent[0][j];
      evalBoard[(11 - j) * 12 +     i   ] = parent[0][j];
      evalBoard[(11 - j) * 12 + (11 - i)] = parent[0][j];
    }
  }

  // $B;M6y(B
  evalBoard[0] = 0;
  evalBoard[11] = 0;
  evalBoard[132] = 0;
  evalBoard[143] = 0;
}

/*! @brief $B;R$NI>2A%\!<%I$rJV$9(B
 @param[in] index $B;R$I$b$N%$%s%G%C%/%9(B
 @param[out] evalBoard $BI>2A%\!<%I(B(int$B7?(B1$B<!85G[Ns(B)
*/
void GeneticAlgorithmforReversi::getEvaluateFunctionOfChild(int index, int* evalBoard)
{
  index = index % 10;

  for(i = 0; i < 6; i++)
  {
    for(j = i; j < 6; j++)
    {
      evalBoard[    i    * 12 +     j   ] = children[index][j];
      evalBoard[    i    * 12 + (11 - j)] = children[index][j];
      evalBoard[    j    * 12 +     i   ] = children[index][j];
      evalBoard[    j    * 12 + (11 - i)] = children[index][j];
      evalBoard[(11 - i) * 12 +     j   ] = children[index][j];
      evalBoard[(11 - i) * 12 + (11 - j)] = children[index][j];
      evalBoard[(11 - j) * 12 +     i   ] = children[index][j];
      evalBoard[(11 - j) * 12 + (11 - i)] = children[index][j];
    }
  }

  // $B;M6y(B
  evalBoard[0] = 0;
  evalBoard[11] = 0;
  evalBoard[132] = 0;
  evalBoard[143] = 0;
}

/*! @brief $B;R%\!<%I$N@8@.(B
*/
void GeneticAlgorithmforReversi::createChildren()
{
  choiceParent();
  crossParent();
  mutation();
}

/*! @brief $B;R6!$N>!?t$r%;%C%H(B
 @param[in] index $B;R6!$N%$%s%G%C%/%9(B
 @param[in] wins $B>!?t(B
*/
void setNumberOfWins(int index, int wins)
{
  numberOfWins[i] = wins;
}

/*! @brief $B?F$NA*Br(B
*/
void GeneticAlgorithmforReversi::choiceParent()
{
  int bigOnesList[10];
  for(int i = 0; i < 10; i++)
    bigOnesList[i] = i;

  for(int i = 9; i > 1; i++)
  {
    for(int j = 0; j < i; j++)
    {
      if(numberOfWins[j] < numberOfWins[j + 1])
      {
        int tmp = numberOfWins[j];
	numberOfWins[j] = numberOfWins[j + 1];
	numberOfWins[j + 1] = tmp;
	tmp = bigOnesList[j];
	bigOnesList[j] = bigOnesList[j + 1];
	bigOnesList[j + 1] = tmp;
      }
    }
  }

  for(int i = 0; i < 20; i++)
  {
    parent[0][i] = children[bigOnesList[0]][i];
    parent[1][i] = children[bigOnesList[1]][i];
  }
  initNumberOfWins();
}

/*! @brief $B8r:5(B
*/
GeneticAlgorithmforReversi::crossParent()
{
<<<<<<< HEAD
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 20; j++)
    {
      children[i][j] = parent[rand() % 2][j];
    }
  }
=======
  
>>>>>>> bc80acb6bea91b80d3545ba28806c8b5d9331e83
}

/*! @brief $BFMA3JQ0[(B
*/
GeneticAlgorithmforReversi::mutation()
{
  for(int i = 0; i < 10; i++)
  {
    for(int j = 1; j < 20; j++)
    {
      if(rand() % 50 == 0)
        children[i][j] += rand() % 40 - 20;
    }
  }
}

/*! @brief $B;R%\!<%I$N=i4|2=(B
*/
void GeneticAlgorithmforReversi::initChildren()
{
  for(int i = 0; i < 10; i++)
  {
    children[i][0] = 0;
    for(int j = 1; j < 20; j++)
    {
      children[i][j] = (rand() % 240) - 120;
    }
  }
}

/*! @brief numberOfWins$B$N=i4|2=(B
*/
void GeneticAlgorithmforReversi::initNumberOfWins()
{
  for(int i = 0; i < 10; i++)
  {
    numberOfWins[i] = 0;
  }
}

