/*! @file
 @brief コンストラクタ
 @author 新井
 @date 2017.6.2
*/

#include "getetic.h"

#include <stdlib.h>
#include <time.h>

/*! @brief コンストラクタ
*/
GeneticAlgorithmforReversi::GeneticAlgorithmforReversi()
{
  srand(time(NULL));
  initChildren();
  initNumberOfWins();
}

/*! @brief 親の評価ボードを返す
 @param[in] index 親のインデックス(0か1)
 @param[out] evalBoard 評価ボード(int型1次元配列)
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

  // 四隅
  evalBoard[0] = 0;
  evalBoard[11] = 0;
  evalBoard[132] = 0;
  evalBoard[143] = 0;
}

/*! @brief 子の評価ボードを返す
 @param[in] index 子どものインデックス
 @param[out] evalBoard 評価ボード(int型1次元配列)
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

  // 四隅
  evalBoard[0] = 0;
  evalBoard[11] = 0;
  evalBoard[132] = 0;
  evalBoard[143] = 0;
}

/*! @brief 子ボードの生成
*/
void GeneticAlgorithmforReversi::createChildren()
{
  choiceParent();
  crossParent();
  mutation();
}

/*! @brief 子供の勝数をセット
 @param[in] index 子供のインデックス
 @param[in] wins 勝数
*/
void setNumberOfWins(int index, int wins)
{
  numberOfWins[i] = wins;
}

/*! @brief 親の選択
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

/*! @brief 交叉
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

/*! @brief 突然変異
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

/*! @brief 子ボードの初期化
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

/*! @brief numberOfWinsの初期化
*/
void GeneticAlgorithmforReversi::initNumberOfWins()
{
  for(int i = 0; i < 10; i++)
  {
    numberOfWins[i] = 0;
  }
}

