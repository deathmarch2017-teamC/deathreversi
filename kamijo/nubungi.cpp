/* @file
 @brief minimax$BK!<BAuESCf(B
 @author $B>e[j(B
 @date 2017.5.29
*/

#include "Reversi_AI_Random.h"
#include <ctime>
#include <cstdlib>


/*! @brief $B%3%s%9%H%i%/%?(B
*/

Reversi_AI_Random::Reversi_AI_Random()
{
  Berserker_Soul = false;
  srand(time(NULL));
}

/*! @brief $B<!$N<j$rJV$94X?t(B
 @param[in] board $BHWLL>pJs(B
 @param[in] flagin $B%5!<%P$+$i<u?.$7$?%U%i%0(B
 @param[out] x $B<!$N<j$N(Bx$B:BI8(B
 @param[out] y $B<!$N<j$N(By$B:BI8(B
 @param[out] flagout $B%5!<%P$XAw?.$9$k%U%i%0>pJs(B
*/



//$BI>2A4X?t%[%2%[%2(B
int hogehoge()
{
  int r;
  r = rand() % 10;
  return r;
}


void Reversi_AI_Random::return_move(Board board, int flagin, int &x, int &y, int &flagout)
{
  if((flagin & ACFLAG) == 0)
    {
    // branch by movable position
    int movablePosNum = board.getMovablePos().size();
    // no movable position
    if(movablePosNum == 0)
    {
      // pass
      *x = 0;
      *y = 0;
      *flagout = PSFLAG;
    }
    else
      {
	//$BC5:w$N?<$5(B
	int limit = 2;

	//$B<+J,$N<j$rD4$Y$k4X?t(B
	int maxlevel(int limit)
	{
	  if(limit == 0)
	    //$BI>2ACM$rJV$9(B
	    return hogehoge();

	  //$BBG$D<j$rA48!:w(B
	  std::vector<Point>points = board.getMovable();
	  Point p = points;
	  for(Point p : p )
		     {
		       int score , score_max;
		       //$B<+J,$N<j$rBG$D(B
		       move(Point p);
		       score = minleve(limit-1);
		       //$B#1$DA0$N<j$KLa$9(B
		       undo();
		       if(score > score_max)
			 {
			   score_max = score;
			 }
		     }
	  return score_max;
	}



	//$BAj<j$N<j$rD4$Y$k4X?t(B
	int minleverl(int limit)
	{
	  if(limit == 0)
	    //$BI>2ACM$rJV$9(B
	    return hogehoge();

	  //$BBG$D<j$rA48!:w(B
	  std::vector<Point>points = board.getMovable();
	  Point p = points;
	  for(Point p : p )
		     {
		       int score , score_min;
		       //$B<+J,$N<j$rBG$D(B
		       move(Point p);
		       score = maxleve(limit-1);
		       //$B#1$DA0$N<j$KLa$9(B
		       undo();
		       if(score > score_max)
			 {
			   score_min = score;
			 }
		     }
	  return score_min;

	  *x = p.x; 
	  *y = p.y;
	}


      // MTFLAG option
      if(Berserker_Soul == false && board.getTurns() >= 10)
      {
        // use MT with 5%
        *flagout = (rand() % 20 == 0) ? MTFLAG : 0;
	Berserker_Soul = ((*flagout & MTFLAG) != 0) ? true : false;
      }
      else{
        // player can use MT once time in a game.
        *flagout = 0;
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
    *x = p.x;
    *y = p.y;
    *flagout = 0;
  }
}

    Contact GitHub API Training Shop Blog About 

