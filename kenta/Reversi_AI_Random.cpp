/* @file
 @brief ランダムAI
 @author 新井
 @date 2017.5.23
*/

#include "Reversi_AI_Random.h"
#include <ctime>
#include <cstdlib>

/*! @brief コンストラクタ
*/

Reversi_AI_Random::Reversi_AI_Random()
{
  Berserker_Soul = false;
  use_of_MT = false;
  srand(time(NULL));
}

/*! @brief 次の手を返す関数
 @param[in] board 盤面情報
 @param[in] flagin サーバから受信したフラグ
 @param[out] x 次の手のx座標
 @param[out] y 次の手のy座標
 @param[out] flagout サーバへ送信するフラグ情報
*/

void Reversi_AI_Random::return_move(Board board, int flagin, int &x, int &y, int &flagout)
{
  if((flagin & ACFLAG) == 0){
    // branch by movable position
    int movablePosNum = board.getMovablePos().size();
    // no movable position
    if(movablePosNum == 0)
    {
      // pass
      x = 0;
      y = 0;
      flagout = PSFLAG;
    }
    else{
      // decides a random move
      std::vector<Point> points = board.getMovablePos();
      Point p = points[rand() % points.size()];
      x = p.x;
      y = p.y;

      // MTFLAG option
      if(Berserker_Soul == false && board.getTurns() >= 10)
      {
        // use MT with 5%
        flagout = (rand() % 20 == 0) ? MTFLAG : 0;
	Berserker_Soul = ((flagout & MTFLAG) != 0) ? true : false;
      }
      else{
        // player can use MT once time in a game.
        flagout = 0;
      }
    }
  }
  else{
    // when attack chance
    Color opponentColor = -1 * board.getCurrentColor();
    std::vector<Point> points;
    // collect all opponent's coordinate
    for(int i = 1; i <= 12; i++)
    {
      for(int j = 1; j <= 12; j++)
      {
        Point p(i, j);
	if(board.getColor(p) == opponentColor)
	{
	  points.push_back(p);
	}
      }
    }

    // decides a move with random
    Point p = points[rand() % points.size()];
    x = p.x;
    y = p.y;
    flagout = 0;
  }
}

/*! @brief MTを使うべきか判定する関数
 @param[in] board 盤面情報
 @param[out] firstPoint 最初の手における座標
 @param[out] secondPoint MTにおける座標
 @return MTを使うべきかをbool値で返す．trueなら使うべきと判定
*/
bool check_to_use_MT(Board b, Point &first_point, Point &second_point){
  std::vector<Point> first_movable_pos = board.getMovablePos();

  for(int i = 0; i < first_movable_pos.size(); i++)
  {
    first_movable_pos(i).flag = MTFLAG;
    board.move(first_movable_pos(i));
    std::vector<Point> second_movable_pos = board.getMovablePos();
    for(int j = 0; j < second_movable_pos.size(); j++)
    {
      board.move(second_movable_pos(j));
      if(board.getMovablePos().size() == 0)
      {
        first_point.x  = first_movable_pos(i).x;
        first_point.y  = first_movable_pos(i).y;
	first_point.flag = MTFLAG;
        second_point.x = second_movable_pos(i).x;
        second_point.y = second_movable_pos(i).y;
	first_point.flag = 0;
	return true;
      }
      board.undo(second_movable_pos(j));
    }
    board.undo(first_movable_pos(i));
  }

  return false;
}

