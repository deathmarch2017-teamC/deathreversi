/*! @file
 @brief ランダムAI
 @author 新井
 @date 2017.5.23
*/

#ifndef REVERSI_AI_H
#define REVERSI_AI_H

#include "Board.h"
#include <iostream>
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

class Reversi_AI_Minimax
{
  public:
    Reversi_AI_Minimax();
    void notice_opponent_use_MT();
    void return_move(Board b, int flagin, int &x, int &y, int &flagout);
  private:
    bool check_to_use_MT(Board b, Point &first_Point, Point &second_Point);
    void init_eval_board();
    Point Minimax(Board b, int depth);
    int evaluate_board(Board b);
    int maxlevel(int limit, Board board);
    int minlevel(int limit, Board board);
    std::vector<char> eval_board;
    bool Berserker_Soul;
    bool use_of_MT;
    bool opponent_MT_FLAG;
    Point tp;
    bool set_tp;
};

class Reversi_AI_ab
{
  public:
    Reversi_AI_ab(Color color);
    void notice_opponent_use_MT();
    void return_move(Board b, int flagin, int &x, int &y, int &flagout);
  private:
    bool check_to_use_MT(Board b, Point &p);
    void init_eval_board();
    Point ab(Board b, int depth);
    int evaluate_board(Board b);
    int maxlevel(int limit, Board board, int alpha, int beta);
    int minlevel(int limit, Board board, int alpha, int beta);
    Color myColor;
    std::vector<char> eval_board;
    bool Berserker_Soul;
    bool use_of_MT;
    bool opponent_MT_FLAG;
    Point tp;
    bool set_tp;
    char stage;
};


#endif
