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
  opponent_MT_FLAG = false;
  set_tp = false;
  srand(time(NULL));
}

/*! @brief 相手がMTを使用したことを通知する関数
*/
void Reversi_AI_Random::notice_opponent_use_MT()
{
  opponent_MT_FLAG = true;
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
    // second move which you used MT
    if(set_tp)
    {
      x = tp.x;
      y = tp.y;
      flagout = tp.flag;
      set_tp = false;
      return;
    }
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
      // check to use MT
      if(Berserker_Soul == false && board.getTurns() >= 9)
      {
        Point p1, p2;
        if(check_to_use_MT(b, p1, p2))
	{
	  x = p1.x;
	  y = p1.y;
	  flagout = MTFLAG;
	  tp.x = p2.x;
	  tp.y = p2.y;
	  tp.flag = 0;
	  set_tp = true;
	  break;
	}
      }
        
      // decides a random move
      std::vector<Point> points = board.getMovablePos();
      Point p = points[rand() % points.size()];
      x = p.x;
      y = p.y;
      flagout = 0;
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
 @param[out] first_point 最初の手における座標
 @param[out] second_point MTにおける座標
 @return MTを使うべきかをbool値で返す．trueなら使うべきと判定
*/
bool Reversi_AI_Random::check_to_use_MT(Board b, Point &first_point, Point &second_point)
{
  // get movable position
  std::vector<Point> movable_pos = board.getMovablePos();

  // search for a position which the opponent gets all coins
  // remove position from movable_pos, which you mustn't put
  for(int i = 0; i < movable_pos.size(); i++)
  {
    // first move
    board.move(movable_pos(i));
    // then, get movable positions
    std::vector<Point> opponent_movable_pos = board.getMovablePos();
    for(int j = 0; j < opponent_movable_pos.size(); j++)
    {
      // consider the opponent's MT
      if(opponent_MT_FLAG == false)
        opponent_movable_pos(j).flag = MTFLAG;

      // check whether you put a coin
      board.move(opponent_movable_pos(j));
      // if you can't put a coin, remove position from movable_pos
      if(opponent_MT_FLAG == true && board.getMovablePos().size() == 0)
      {
	movable_pos.erase(movable_pos.begin() + i, 1);
	board.undo();
	i--;
	break;
      }
      
      // check whether you put a coin, if your opponent use MT
      bool erase_flag = false;
      if(opponent_MT_FLAG == false)
      {
        // get movable positions
        std::vector<Point> opponent_second_movable_pos = board.getMovablePos();
	// if your opponent get all coins, remove a posision from movable_pos
        for(k = 0; k < opponent_second_movable_pos.size(); k++)
	{
          board.move(opponent_second_movable_pos(k));
	  if(board.getMovablePos().size() == 0)
	  {
	    movable_pos.erase(movable_pos.begin() + i, 1);
	    board.undo();
	    i--;
	    erase_flag = true;
	    break;
	  }
	  board.undo();
	}
      }
      board.undo();
      if(erase_flag)
        break;
    }
    board.undo();
  }

  // if you lose whenever you don't use MT, use MT
  if(movable_pos.size() == 0)
  {
    movable_pos = board.getMovablePos();
    for(int i = 0; i < movable_pos.size(); i++)
    {
      // move random
      int p1 = rand() % movable_pos.size();
      movable_pos(p1).flag = MTFLAG;
      board.move(movable_pos(p1));
      std::vector<Point> second_movable_pos = board.getMovablePos();
      // decide coordinates to put coins
      if(second_movable_pos.size() != 0)
      {
        int p2 = rand() % second_movable_pos.size();
	second_movable_pos(p2).flag = 0;
        first_point.x  = movable_pos(p1).x;
        first_point.y  = movable_pos(p1).y;
        first_point.flag = MTFLAG;
        second_point.x = second_movable_pos(p2).x;
        second_point.y = second_movable_pos(p2).y;
        first_point.flag = 0;
        return true;
      }
      board.undo();
    }
    return false;
  }

  // search for a position which you get all coins
  for(int i = 0; i < movable_pos.size(); i++)
  {
    // first move
    movable_pos(i).flag = MTFLAG;
    board.move(movable_pos(i));
    // then, get movable position
    std::vector<Point> second_movable_pos = board.getMovablePos();
    // search for a move which you get all discs
    for(int j = 0; j < second_movable_pos.size(); j++)
    {
      // second move
      board.move(second_movable_pos(j));
      // judge if you get all discs
      if(board.getMovablePos().size() == 0)
      {
        // if you do, return the following data
        first_point.x  = movable_pos(i).x;
        first_point.y  = movable_pos(i).y;
	first_point.flag = MTFLAG;
        second_point.x = second_movable_pos(i).x;
        second_point.y = second_movable_pos(i).y;
	first_point.flag = 0;
	return true;
      }
      // if second move isn't suitable, undo the board
      board.undo();
    }
    // if first move isn't suitable, undo the board
    board.undo();
  }

  return false;
}

