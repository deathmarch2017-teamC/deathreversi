/*! @file
 @brief ランダムAI
 @author 新井
 @date 2017.5.23
*/

#ifndef REVERSI_AI_H
#define REVERSI_AI_H

#include "Board.h"

/*! @brief AIのクラス
*/
class Reversi_AI
{
  public:
    Reversi_AI();
    void notice_opponent_use_MT();
    void return_move(Board b, int flagin, int &x, int &y, int &flagout);
  private:
    bool check_to_use_MT(Board b, Point &first_Point, Point &second_Point);
    bool Berserker_Soul;
    bool use_of_MT;
    bool opponent_MT_FLAG;
    Point tp;
    bool set_tp;
};

#endif
