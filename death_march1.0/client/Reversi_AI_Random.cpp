/* @file
 @brief ランダムAI
 @author 新井
 @date 2017.5.23
*/

#include "Reversi_AI.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

/* public functions */

/*! @brief コンストラクタ
*/
Reversi_AI::Reversi_AI()
{
  Berserker_Soul = false;
  use_of_MT = false;
  opponent_MT_FLAG = false;
  set_tp = false;
  srand(time(NULL));
}

/*! @brief 相手がMTを使用したことを通知する関数
*/
void Reversi_AI::notice_opponent_use_MT()
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

void Reversi_AI::return_move(Board board, int flagin, int &x, int &y, int &flagout)
{
  if((flagin & ACFLAG) == 0){
    // second move which you used MT
    if(set_tp)
    {
      x = tp.x;
      y = tp.y;
      flagout = tp.flag;
      set_tp = false;
      std::cout << "tp: " << x << "," << y << std::endl;
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
        if(check_to_use_MT(board, p1, p2))
        {
          x = p1.x;
          y = p1.y;
          flagout = p1.flag;
          tp.x = p2.x;
          tp.y = p2.y;
          tp.flag = p2.flag;
          set_tp = true;
          // sigenobu revised
          Berserker_Soul = true;
          return;
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
bool Reversi_AI::check_to_use_MT(Board b, Point &first_point, Point &second_point)
{
  int call_move = 0;
  // get movable position
  std::vector<Point> movable_pos = b.getMovablePos();

  // search for a position which the opponent gets all coins
  // remove position from movable_pos, which you mustn't put
  for(int i = 0; i < movable_pos.size(); i++)
  {
    // first move
    b.move(movable_pos[i]);
    call_move++;
    // then, get movable positions
    std::vector<Point> opponent_movable_pos = b.getMovablePos();
    for(int j = 0; j < opponent_movable_pos.size(); j++)
    {
      // check whether you put a coin
      b.move(opponent_movable_pos[j]);
      call_move++;
      // if you can't put a coin, remove position from movable_pos
      if(b.getMovablePos().size() == 0)
      {
        //sigenobu revised
        //movable_pos.erase(movable_pos.begin() + i, 1);
        movable_pos.erase(movable_pos.begin() + i);
        i--;
        b.undo();
	call_move--;
        break;
      }
      b.undo();
      call_move--;
      
      if(opponent_MT_FLAG == false)
      {
        // check whether you put a coin
        opponent_movable_pos[j].flag = MTFLAG;
        b.move(opponent_movable_pos[j]);
	call_move++;

        // check whether you put a coin, if your opponent use MT
        bool erase_flag = false;
        // get movable positions
        std::vector<Point> opponent_second_movable_pos = b.getMovablePos();
	
        // if your opponent get all coins, remove a posision from movable_pos
        for(int k = 0; k < opponent_second_movable_pos.size(); k++)
        {
          b.move(opponent_second_movable_pos[k]);
	  call_move++;
          if(b.getMovablePos().size() == 0)
          {
            // sigenobu revised
            movable_pos.erase(movable_pos.begin() + i);
            i--;
            b.undo();
	    call_move--;
            erase_flag = true;
            break;
          }
          b.undo();
	  call_move--;
        }
        b.undo();
	call_move--;
        if(erase_flag)
          break;
      }
    }
    b.undo();
    call_move--;
  }

  std::cout << "----------------------------------------------------------" << std::endl;
  std::cout << "call_move: " << call_move << std::endl;
  std::cout << "----------------------------------------------------------" << std::endl;

  // if you lose whenever you don't use MT, use MT
  if(movable_pos.size() == 0)
  {
    movable_pos = b.getMovablePos();
    for(int i = 0; i < movable_pos.size(); i++)
    {
      // move random
      int p1 = rand() % movable_pos.size();
      movable_pos[p1].flag = MTFLAG;
      b.move(movable_pos[p1]);
      call_move++;
      std::vector<Point> second_movable_pos = b.getMovablePos();
      // decide coordinates to put coins
      if(second_movable_pos.size() != 0)
      {
        int p2 = rand() % second_movable_pos.size();
	second_movable_pos[p2].flag = 0;
        first_point.x  = movable_pos[p1].x;
        first_point.y  = movable_pos[p1].y;
        first_point.flag = MTFLAG;
        second_point.x = second_movable_pos[p2].x;
        second_point.y = second_movable_pos[p2].y;
        second_point.flag = 0;
        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << "level0" << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;
        return true;
      }
      b.undo();
      call_move--;
    }
    return false;
  }

  std::cout << "----------------------------------------------------------" << std::endl;
  std::cout << "call_move: " << call_move << std::endl;
  std::cout << "----------------------------------------------------------" << std::endl;

  // search for a position which you get all coins
  for(int i = 0; i < movable_pos.size(); i++)
  {
    // first move
    int p1 = rand() % movable_pos.size();
    movable_pos[p1].flag = MTFLAG;
    b.move(movable_pos[p1]);
    call_move++;
    // then, get movable position
    std::vector<Point> second_movable_pos = b.getMovablePos();
    // search for a move which you get all discs
    for(int j = 0; j < second_movable_pos.size(); j++)
    {
      // second move
      int p2 = rand() % second_movable_pos.size();
      b.move(second_movable_pos[p2]);
      call_move++;
      // judge if you get all discs
      if(b.getMovablePos().size() == 0)
      {
        // if you do, return the following data
        first_point.x  = movable_pos[p1].x;
        first_point.y  = movable_pos[p1].y;
	first_point.flag = MTFLAG;
        second_point.x = second_movable_pos[p2].x;
        second_point.y = second_movable_pos[p2].y;
	second_point.flag = 0;
        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << "level1" << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;
	return true;
      }
      // if second move isn't suitable, undo the board
      b.undo();
      call_move--;
    }
    // if first move isn't suitable, undo the board
    b.undo();
    call_move--;
  }

  std::cout << "----------------------------------------------------------" << std::endl;
  std::cout << "call_move: " << call_move << std::endl;
  std::cout << "----------------------------------------------------------" << std::endl;

  return false;
}

