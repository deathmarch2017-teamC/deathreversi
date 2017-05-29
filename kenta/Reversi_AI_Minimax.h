/*! @file
 @brief MinimaxAI
 @author 新井
 @date 2017.5.23
*/

#ifndef REVERSI_AI_MINIMAX_H
#define REVERSI_AI_MINIMAX_H

#include "Board.h"

/*! @brief AIのクラス
*/
class Reversi_AI_Minimax
{
  public:
    Reversi_AI_Minimax();
    void return_move(Board b, int flagin, int &x, int &y, int &flagout);
    bool check_to_use_MT(Board b, Point &first_Point, Point &second_Point);
  private:
    bool Berserker_Soul;
    bool use_of_MT;
    bool opponent_MT_FLAG;
    Point tp;
    bool set_tp;
};

#endif
