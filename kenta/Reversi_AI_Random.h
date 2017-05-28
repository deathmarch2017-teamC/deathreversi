/*! @file
 @brief ランダムAI
 @author 新井
 @date 2017.5.23
*/

#ifndef REVERSI_AI_RANDOM_H
#define REVERSI_AI_RANDOM_H

#include "Board.h"

/*! @brief AIのクラス
*/
class Reversi_AI_Random{
  public:
    Reversi_AI_Random();
    void return_move(Board b, int flagin, int &x, int &y, int &flagout);
    bool check_to_use_MT(Board b, Point &first_Point, Point &second_Point);
  private:
    bool Berserker_Soul;
    bool use_of_MT;
};

#endif
