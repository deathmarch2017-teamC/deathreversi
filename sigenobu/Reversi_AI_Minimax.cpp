/* @file
 @brief MinimaxAI
 @author 重信
 @date 2017.5.30
*/

#include "Reversi_AI.h"
#include <ctime>
#include <cstdlib>

#define DEPTH 3
#define NUM_MAX 65535

Reversi_AI::Reversi_AI()
{
  Berserker_Soul = false;
  use_of_MT = false;
  opponent_MT_FLAG = false;
  set_tp = false;
  init_eval_board();
  srand(time(NULL));
}

/*! @brief eval_boardの初期化
*/
void Reversi_AI::init_eval_board()
{
  eval_board = {
  {   0, 100, -80,  80,  20,   5,   5,  20,  80, -80, 100,   0},
  { 100, -90, -60,  -5,  -5,  -5,  -5,  -5,  -5, -60, -90, 100},
  { -80, -60,  20,  10,  10,   3,   3,  10,  10,  20, -60, -80},
  {  80,  -5,  10,   5,   5,   3,   3,   5,   5,  10,  -5,  80},
  {  20,  -5,  10,   5,   5,   3,   3,   5,   5,   5,  10,  -5},
  {   5,  -5,   3,   3,   3,   3,   3,   3,   3,   3,  -5,   5}
  {   5,  -5,   3,   3,   3,   3,   3,   3,   3,   3,  -5,   5},
  {  20,  -5,  10,   5,   5,   3,   3,   5,   5,   5,  10,  -5},
  {  80,  -5,  10,   5,   5,   3,   3,   5,   5,  10,  -5,  80},
  { -80, -60,  20,  10,  10,   3,   3,  10,  10,  20, -60, -80},
  { 100, -90, -60,  -5,  -5,  -5,  -5,  -5,  -5, -60, -90, 100},
  {   0, 100, -80,  80,  20,   5,   5,  20,  80, -80, 100,   0}};
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
	      flagout = MTFLAG;
	      tp.x = p2.x;
	      tp.y = p2.y;
	      tp.flag = 0;
	      set_tp = true;
	      // sigenobu revised
	      Berserker_Soul = true;
	      return;
	    }
	}
        

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

    // decides a move with minimax
    Point p = Minimax(board, DEPTH);
    x = p.x;
    y = p.y;
    flagout = 0;
  }
}

/*! @brief Minimax法による座標決定
 @param[in] board 盤面情報
 @param[in] depth 探索する深さ
 @return 評価値
*/
Point Minimax(Board b, int depth)
{
  Point mymove;
  int eval, eval_max = -NUM_MAX;

  std::vector<Point>points = board.getMovable();
  int score , score_max = -NUM_MAX;
  for(Point p : points )
    {
      b.move(p);
      eval = minlevel(depth, b);
      b.undo();
      if(eval > eval_max){
	mymove = p;
      }
    }
  
  return mymove;
}
/*! @brief 評価値の計算
 @param[in] board 盤面情報
 @return 評価値
*/
int evaluate_board(Board b)
{
  int i, j, val = 0;
  Point tmp;
  for(i = 0; i < BOARD_SIZE; i++){
    for(j = 0; j < BOARD_SIZE; j++){
      tmp.x = i+1;
      tmp.y = j+1;
      val += eval_board[i][j] * board.getColor(tmp);
    }
  }
  if(board.getCurrentColor() == WHITE){
    val = val * -1;
  }
  return val;
}

/*! @brief 自分の手を調べる関数
 @param[in] limit 探索の深さ
 @return そのノードの評価値
*/

int maxlevel(int limit, board board){

  if(limit == 0)
    //評価値を返す
    return evaluate_board(board);

  //打つ手を全検索
  std::vector<Point>points = board.getMovable();
  int score , score_max = -NUM_MAX;
  for(Point p : points )
    {
      //自分の手を打つ
      board.move(p);
      score = minlevel(limit-1);
      //１つ前の手に戻す
      board.undo();
      if(score > score_max)
	{
	  score_max = score;
	}
    }
  return score_max;
}

int minlevel(int limit, board board)
{
  if(limit == 0)
    //評価値を返す
    return evaluate_board(board);

  //打つ手を全検索
  std::vector<Point>points = board.getMovable();
  int score , score_min = NUM_MAX;
  for(Point p : points )
    {
      //自分の手を打つ
      board.move(p);
      score = maxlevel(limit-1);
      //１つ前の手に戻す
      board.undo();
      if(score > score_max)
	{
	  score_min = score;
	}
    }
  return score_min;
}

  /*! @brief MTを使うべきか判定する関数
    @param[in] board 盤面情報
    @param[out] first_point 最初の手における座標
    @param[out] second_point MTにおける座標
    @return MTを使うべきかをbool値で返す．trueなら使うべきと判定
  */
  bool Reversi_AI::check_to_use_MT(Board b, Point &first_point, Point &second_point)
  {
    // get movable position
    std::vector<Point> movable_pos = b.getMovablePos();

    // search for a position which the opponent gets all coins
    // remove position from movable_pos, which you mustn't put
    for(int i = 0; i < movable_pos.size(); i++)
      {
	// first move
	b.move(movable_pos[i]);
	// then, get movable positions
	std::vector<Point> opponent_movable_pos = b.getMovablePos();
	for(int j = 0; j < opponent_movable_pos.size(); j++)
	  {
	    // consider the opponent's MT
	    if(opponent_MT_FLAG == false)
	      opponent_movable_pos[j].flag = MTFLAG;

	    // check whether you put a coin
	    b.move(opponent_movable_pos[j]);
	    // if you can't put a coin, remove position from movable_pos
	    if(opponent_MT_FLAG == true && b.getMovablePos().size() == 0)
	      {
		//sigenobu revised
		//movable_pos.erase(movable_pos.begin() + i, 1);
		movable_pos.erase(movable_pos.begin() + i);
		b.undo();
		i--;
		break;
	      }
      
	    // check whether you put a coin, if your opponent use MT
	    bool erase_flag = false;
	    if(opponent_MT_FLAG == false)
	      {
		// get movable positions
		std::vector<Point> opponent_second_movable_pos = b.getMovablePos();
		// if your opponent get all coins, remove a posision from movable_pos
		for(int k = 0; k < opponent_second_movable_pos.size(); k++)
		  {
		    b.move(opponent_second_movable_pos[k]);
		    if(b.getMovablePos().size() == 0)
		      {
			// sigenobu revised
			movable_pos.erase(movable_pos.begin() + i);
			b.undo();
			i--;
			erase_flag = true;
			break;
		      }
		    b.undo();
		  }
	      }
	    b.undo();
	    if(erase_flag)
	      break;
	  }
	b.undo();
      }

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
		first_point.flag = 0;
		return true;
	      }
	    b.undo();
	  }
	return false;
      }

    // search for a position which you get all coins
    for(int i = 0; i < movable_pos.size(); i++)
      {
	// first move
	movable_pos[i].flag = MTFLAG;
	b.move(movable_pos[i]);
	// then, get movable position
	std::vector<Point> second_movable_pos = b.getMovablePos();
	// search for a move which you get all discs
	for(int j = 0; j < second_movable_pos.size(); j++)
	  {
	    // second move
	    b.move(second_movable_pos[j]);
	    // judge if you get all discs
	    if(b.getMovablePos().size() == 0)
	      {
		// if you do, return the following data
		first_point.x  = movable_pos[i].x;
		first_point.y  = movable_pos[i].y;
		first_point.flag = MTFLAG;
		second_point.x = second_movable_pos[i].x;
		second_point.y = second_movable_pos[i].y;
		first_point.flag = 0;
		return true;
	      }
	    // if second move isn't suitable, undo the board
	    b.undo();
	  }
	// if first move isn't suitable, undo the board
	b.undo();
      }

    return false;
  }

