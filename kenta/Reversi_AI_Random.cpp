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
  MT_FLAG = false;
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

    // decides a random move
    Point p = points[rand() % points.size()];
    x = p.x;
    y = p.y;
    flagout = 0;
  }
}

