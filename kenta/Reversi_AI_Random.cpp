/* @file
 @brief $B%i%s%@%`(BAI
 @author $B?70f(B
 @date 2017.5.23
*/

#include "Reversi_AI_Random.h"
#include <ctime>
#include <cstdlib>

/*! @brief $B%3%s%9%H%i%/%?(B
*/

Reversi_AI_Random::Reversi_AI_Random()
{
  Berserker_Soul = false;
  use_of_MT = false;
  srand(time(NULL));
}

/*! @brief $B<!$N<j$rJV$94X?t(B
 @param[in] board $BHWLL>pJs(B
 @param[in] flagin $B%5!<%P$+$i<u?.$7$?%U%i%0(B
 @param[out] x $B<!$N<j$N(Bx$B:BI8(B
 @param[out] y $B<!$N<j$N(By$B:BI8(B
 @param[out] flagout $B%5!<%P$XAw?.$9$k%U%i%0>pJs(B
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

/*! @brief MT$B$r;H$&$Y$-$+H=Dj$9$k4X?t(B
 @param[in] board $BHWLL>pJs(B
 @param[out] firstPoint $B:G=i$N<j$K$*$1$k:BI8(B
 @param[out] secondPoint MT$B$K$*$1$k:BI8(B
 @return MT$B$r;H$&$Y$-$+$r(Bbool$BCM$GJV$9!%(Btrue$B$J$i;H$&$Y$-$HH=Dj(B
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

