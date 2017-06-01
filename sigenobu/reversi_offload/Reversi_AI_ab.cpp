/* @file
 @brief アルファベータAI
 @author 重信
 @date 2017.5.30
*/

#include "Reversi_AI.h"
#include <ctime>
#include <cstdlib>

#define DEPTH 3
#define NUM_MAX 65535
#define EARLY_STAGE -1
#define MIDDLE_STAGE 0
#define LAST_STAGE 1

/*! @brief コンストラクタ
*/
Reversi_AI_ab::Reversi_AI_ab(Color color)
{
  myColor = color;
  Berserker_Soul = false;
  use_of_MT = false;
  opponent_MT_FLAG = false;
  set_tp = false;
  init_eval_board();
  srand(time(NULL));
  stage = EARLY_STAGE;
  std::cout << "AI:my color is " << myColor << " !!!" << std::endl;
}

/*! @brief eval_boardの初期化
*/
void Reversi_AI_ab::init_eval_board()
{
   char eval[] = {
       0, 100, -80,  80,  20,  -5,  -5,  20,  10, -80, 100,   0,\
     100, -90, -60,  -5,  -5,  -5,  -5,  -5,  -5, -60, -90, 100,\
     -80, -60,  20,  -5,  -5, -10, -10,  -5,  -5,  20, -60, -80,\
      10,  -5,  -5,  -5,  -5, -10, -10,  -5,  -5,  -5,  -5,  10,\
      -5,  -5,  -5,  -5,  -5, -10, -10,  -5,  -5,  -5,  -5,  -5,\
      -5,  -5, -10, -10, -10, -10, -10, -10, -10, -10,  -5,  -5,\
      -5,  -5, -10, -10, -10, -10, -10, -10, -10, -10,  -5,  -5,\
      -5,  -5,  -5,  -5,  -5, -10, -10,  -5,  -5,  -5,  -5,  -5,\
      10,  -5,  -5,  -5,  -5, -10, -10,  -5,  -5,  -5,  -5,  10,\
     -80, -60,  20,  -5,  -5, -10, -10,  -5,  -5,  20, -60, -80,\
     100, -90, -60,  -5,  -5,  -5,  -5,  -5,  -5, -60, -90, 100,\
       0, 100, -80,  10,  -5,  -5,  -5,  -5,  10, -80, 100,   0};
   eval_board.assign(&eval[0], &eval[BOARD_SIZE*BOARD_SIZE]);
}

/*! @brief 相手がMTを使用したことを通知する関数
*/
void Reversi_AI_ab::notice_opponent_use_MT()
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

void Reversi_AI_ab::return_move(Board board, int flagin, int &x, int &y, int &flagout)
{
  if((flagin & ACFLAG) == 0){
    // second move which you used MT
    // if(set_tp)
    //   {
    // 	x = tp.x;
    // 	y = tp.y;
    // 	flagout = tp.flag;
    // 	set_tp = false;
    // 	return;
    //   }
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
	  Point p1;
	  if(check_to_use_MT(board,p1))
	    {
	      x = p1.x;
	      y = p1.y;
	      flagout = MTFLAG;
	      Berserker_Soul = true;
	      return;
	    }
	  // if(check_to_use_MT(board, p1, p2))
	  //   {
	  //     x = p1.x;
	  //     y = p1.y;
	  //     flagout = MTFLAG;
	  //     tp.x = p2.x;
	  //     tp.y = p2.y;
	  //     tp.flag = 0;
	  //     set_tp = true;
	  //     // sigenobu revised
	  //     Berserker_Soul = true;
	  //     return;
	  //  }
	}
        
      Point p = ab(board, DEPTH);
      x = p.x;
      y = p.y;
      flagout = 0;
    }
  }
  else{
    // when attack chance
    Color opponentColor = -1 * board.getCurrentColor();
    Color boardColor[13][13] = {WALL};
    int getStoneNum;
    int getStoneNumMax = 0;
    std::vector<Point> points;
    // collect all opponent's coordinate
    for(int i = 1; i <= 12; i++)
      {
	for(int j = 1; j <= 12; j++)
	  {
	    Point p(i, j);
	    boardColor[i][j] = board.getColor(p);
	    if((boardColor[i][j]) == opponentColor)
	      {
		points.push_back(p);
	      }
	  }
      }
    // check corner's color 
    if(boardColor[2][1] == opponentColor)
      {
	getStoneNum = 0;
	for (int i = 3; i <= 12; i++){
	  if(boardColor[i][1] == opponentColor)
	    {
	      getStoneNum++;
	    }
	  else
	    {
	      if((boardColor[i][1] == board.getCurrentColor())||(boardColor[i][1] == WALL)) getStoneNum=0;
	      break;
	    }
	}
	if(getStoneNum > getStoneNumMax){
	  x = 2;
	  y = 1;
	  flagout = 0;
	  getStoneNumMax = getStoneNum;
	}
	std::cout << "x:2 y:1" << " getStoneNum:" << getStoneNum << std::endl;
      }
    if(boardColor[2][12] == opponentColor)
      {
	getStoneNum = 0;
	for (int i = 3; i <= 12; i++){
	  if(boardColor[i][12] == opponentColor)
	    {
	      getStoneNum++;
	    }
	  else
	    {
	      if((boardColor[i][12] == board.getCurrentColor())||(boardColor[i][12] == WALL)) getStoneNum=0;
	      break;
	    }
	}
	if(getStoneNum > getStoneNumMax){
	  x = 2;
	  y = 12;
	  flagout = 0;
	  getStoneNumMax = getStoneNum;
	}
	std::cout << "x:2 y:12" << " getStoneNum:" << getStoneNum << std::endl;
      }
    if(boardColor[11][1] == opponentColor)
      {
	getStoneNum = 0;
	for (int i = 10; i >= 1; i--){
	  if(boardColor[i][1] == opponentColor)
	    {
	      getStoneNum++;
	    }
	  else
	    {
	      if((boardColor[i][1] == board.getCurrentColor())||(boardColor[i][1] == WALL)) getStoneNum=0;
	      break;
	    }
	}
	if(getStoneNum > getStoneNumMax){
	  x = 11;
	  y = 1;
	  flagout = 0;
	  getStoneNumMax = getStoneNum;
	}
	std::cout << "x:11 y:1" << " getStoneNum:" << getStoneNum << std::endl;
      }
    if(boardColor[11][12] == opponentColor)
      {
	getStoneNum = 0;
	for (int i = 10; i >= 1; i--){
	  if(boardColor[i][12] == opponentColor)
	    {
	      getStoneNum++;
	    }
	  else
	    {
	      if((boardColor[i][12] == board.getCurrentColor())||(boardColor[i][12] == WALL)) getStoneNum=0;
	      break;
	    }
	}
	if(getStoneNum > getStoneNumMax){
	  x = 11;
	  y = 12;
	  flagout = 0;
	  getStoneNumMax = getStoneNum;
	}
	std::cout << "x:11 y:12" << " getStoneNum:" << getStoneNum << std::endl;
      }
    if(boardColor[1][2] == opponentColor)
      {
	getStoneNum = 0;
	for (int i = 3; i <= 12; i++){
	  if(boardColor[1][i] == opponentColor)
	    {
	      getStoneNum++;
	    }
	  else
	    {
	      if((boardColor[1][i] == board.getCurrentColor())||(boardColor[1][i] == WALL)) getStoneNum=0;
	      break;
	    }
	}
	if(getStoneNum > getStoneNumMax){
	  x = 1;
	  y = 2;
	  flagout = 0;
	  getStoneNumMax = getStoneNum;
	}
	std::cout << "x:1 y:2" << " getStoneNum:" << getStoneNum << std::endl;
      }
    if(boardColor[12][2] == opponentColor)
      {
	getStoneNum = 0;
	for (int i = 3; i <= 12; i++){
	  if(boardColor[12][i] == opponentColor)
	    {
	      getStoneNum++;
	    }
	  else
	    {
	      if((boardColor[12][i] == board.getCurrentColor())||(boardColor[12][i] == WALL)) getStoneNum=0;
	      break;
	    }
	}
	if(getStoneNum > getStoneNumMax){
	  x = 12;
	  y = 2;
	  flagout = 0;
	  getStoneNumMax = getStoneNum;
	}
	std::cout << "x:12 y:2" << " getStoneNum:" << getStoneNum << std::endl;
      }
    if(boardColor[1][11] == opponentColor)
      {
	getStoneNum = 0;
	for (int i = 10; i >= 1; i--){
	  if(boardColor[1][i] == opponentColor)
	    {
	      getStoneNum++;
	    }
	  else
	    {
	      if((boardColor[1][i] == board.getCurrentColor())||(boardColor[1][i] == WALL)) getStoneNum=0;
	      break;
	    }
	}
	if(getStoneNum > getStoneNumMax){
	  x = 1;
	  y = 11;
	  flagout = 0;
	  getStoneNumMax = getStoneNum;
	}
	std::cout << "x:1 y:11" << " getStoneNum:" << getStoneNum << std::endl;
      }
    if(boardColor[12][11] == opponentColor)
      {
	getStoneNum = 0;
	for (int i = 10; i >= 1; i--){
	  if(boardColor[12][i] == opponentColor)
	    {
	      getStoneNum++;
	    }
	  else
	    {
	      if((boardColor[12][i] == board.getCurrentColor())||(boardColor[12][i] == WALL)) getStoneNum=0;
	      break;
	    }
	}
	if(getStoneNum > getStoneNumMax){
	  x = 12;
	  y = 11;
	  flagout = 0;
	  getStoneNumMax = getStoneNum;
	}
	std::cout << "x:12 y:11" << " getStoneNum:" << getStoneNum << std::endl;
      }

    


    if(getStoneNumMax != 0) return;
    // decides a move with minimax
    Point p = points[rand() % points.size()];
    x = p.x;
    y = p.y;
    flagout = 0;
  }
}

/*! @brief ab法による座標決定
 @param[in] board 盤面情報
 @param[in] depth 探索する深さ
 @return 評価値
*/
Point Reversi_AI_ab::ab(Board b, int depth)
{
  Point mymove;
  int eval, eval_max = -NUM_MAX;
  int alpha = -NUM_MAX; 
  int beta = NUM_MAX;
  if(b.getTurns() > 100 && !(stage == LAST_STAGE)){
    std::cout << "LAST_STAGE!!!!!!!!!!!" << std::endl;
    stage = LAST_STAGE;
  }

  if(stage == LAST_STAGE) depth = 3;

  std::vector<Point>points = b.getMovablePos();
  for(int i = 0; i < points.size(); i++)
    {
      b.move(points[i]);
      eval = minlevel(depth, b, alpha, beta);
      b.undo();
      std::cout << "x:" << points[i].x << "y:" << points[i].y << " eval_value = " << eval << std::endl;
      if(eval >= eval_max){
	mymove = points[i];
	eval_max = eval;
      }
    }
  std::cout << "------------------- minimax x:" << mymove.x << " y:" << mymove.y << " -------------------" << std::endl;

  return mymove;
}
/*! @brief 評価値の計算
 @param[in] board 盤面情報
 @return 評価値
*/
int Reversi_AI_ab::evaluate_board(Board b)
{
  int val = 0;

  if(b.countDisc(myColor) == 0){
    val = -NUM_MAX;
    return val;
  }else if(b.countDisc(myColor * -1) == 0){
    val = NUM_MAX;
    return val;
  }

  if(stage == LAST_STAGE){
    //   std::cout << "*********** count disc ***********" << std::endl;
    val = myColor * (b.countDisc(BLACK) - b.countDisc(WHITE));
    return val;
  }

  int i, j;
  Point tmp;
  for(i = 0; i < BOARD_SIZE; i++){
    for(j = 0; j < BOARD_SIZE; j++){
      tmp.x = i+1;
      tmp.y = j+1;
      val += eval_board[i+j*BOARD_SIZE] * b.getColor(tmp);
    }
  }
    val = val * myColor;
  return val;
}

/*! @brief 自分の手を調べる関数
 @param[in] limit 探索の深さ
 @param[in] board 評価対象の盤面
 @param[in] alpha α値
 @param[in] beta β値
 @return そのノードの評価値
*/

int Reversi_AI_ab::maxlevel(int limit, Board board, int alpha, int beta){

  if(limit == 0){
    //評価値を返す
    //    std::cout << "@@@@@@@ end depth_count: " << limit << " @@@@@@@" << std::endl;
    return evaluate_board(board);
  }
  //打つ手を全検索
  std::vector<Point>points = board.getMovablePos();
  if(points.size() == 0){
    std::cout << "@@@@@@@ path depth_count: " << limit << " @@@@@@@" << std::endl;
   return evaluate_board(board);
  }
  int score , score_max = -NUM_MAX;
  for(int i = 0; i < points.size(); i++)
    {
      //自分の手を打つ
      board.move(points[i]);
      score = minlevel(limit-1, board, alpha, beta);
      //１つ前の手に戻す
      board.undo();
      
      //探索中止の判定
      if(score >= beta){
	std::cout << "@@@@@@@ beta depth_count: " << limit << " @@@@@@@" << std::endl;
	return score;
      }
      
      if(score > score_max)
	{
	  score_max = score;
	  //α値の更新
	  if(score_max > alpha) alpha = score_max;
	}
    }
  std::cout << "@@@@@@@ maxlevel depth_count: " << limit << " @@@@@@@" << std::endl;
  return score_max;
}

int Reversi_AI_ab::minlevel(int limit, Board board, int alpha, int beta)
{
  if(limit == 0){
    //評価値を返す
    //  std::cout << "@@@@@@@ end depth_count: " << limit << " @@@@@@@" << std::endl;
  return evaluate_board(board);
  }
  //打つ手を全検索
  std::vector<Point>points = board.getMovablePos();
  if(points.size() == 0){
    //    std::cout << "@@@@@@@ depth_count: " << limit << " @@@@@@@" << std::endl;
   return evaluate_board(board);
  } 
  int score , score_min = NUM_MAX;
  for(int i = 0; i < points.size(); i++)
    {
      //自分の手を打つ
      board.move(points[i]);
      score = maxlevel(limit-1, board, alpha, beta);
      //１つ前の手に戻す
      board.undo();

      //探索打ち切りの判定
      if(score <= alpha){
	std::cout << "@@@@@@@ alpha depth_count: " << limit << " @@@@@@@" << std::endl;
	return score;
      }

      if(score < score_min)
	{
	  score_min = score;
	  //β値の更新
	  if(score_min < beta) beta = score_min;
	}
    }
   std::cout << "@@@@@@@ minlevel depth_count: " << limit << " @@@@@@@" << std::endl;
  return score_min;
}

  /*! @brief MTを使うべきか判定する関数
    @param[in] board 盤面情報
    @param[out] first_point 最初の手における座標
    @param[out] second_point MTにおける座標
    @return MTを使うべきかをbool値で返す．trueなら使うべきと判定
  */

bool Reversi_AI_ab::check_to_use_MT(Board b, Point &point)
{
  std::vector<Point> movable_pos = b.getMovablePos();
  if(movable_pos.size() >= 5){
    point = movable_pos[rand() % movable_pos.size()];
    return true;
  }
  return false;

  /*! @brief MTを使うべきか判定する関数
    @param[in] board 盤面情報
    @param[out] first_point 最初の手における座標
    @param[out] second_point MTにおける座標
    @return MTを使うべきかをbool値で返す．trueなら使うべきと判定
  */

// bool Reversi_AI_ab::check_to_use_MT(Board b, Point &first_point, Point &second_point)
  // {
  //   // get movable position
  //   std::vector<Point> movable_pos = b.getMovablePos();

  //   // search for a position which the opponent gets all coins
  //   // remove position from movable_pos, which you mustn't put
  //   for(int i = 0; i < movable_pos.size(); i++)
  //     {
  // 	// first move
  // 	b.move(movable_pos[i]);
  // 	// then, get movable positions
  // 	std::vector<Point> opponent_movable_pos = b.getMovablePos();
  // 	for(int j = 0; j < opponent_movable_pos.size(); j++)
  // 	  {
  // 	    // consider the opponent's MT
  // 	    if(opponent_MT_FLAG == false)
  // 	      opponent_movable_pos[j].flag = MTFLAG;

  // 	    // check whether you put a coin
  // 	    b.move(opponent_movable_pos[j]);
  // 	    // if you can't put a coin, remove position from movable_pos
  // 	    if(opponent_MT_FLAG == true && b.getMovablePos().size() == 0)
  // 	      {
  // 		//sigenobu revised
  // 		//movable_pos.erase(movable_pos.begin() + i, 1);
  // 		movable_pos.erase(movable_pos.begin() + i);
  // 		b.undo();
  // 		i--;
  // 		break;
  // 	      }
      
  // 	    // check whether you put a coin, if your opponent use MT
  // 	    bool erase_flag = false;
  // 	    if(opponent_MT_FLAG == false)
  // 	      {
  // 		// get movable positions
  // 		std::vector<Point> opponent_second_movable_pos = b.getMovablePos();
  // 		// if your opponent get all coins, remove a posision from movable_pos
  // 		for(int k = 0; k < opponent_second_movable_pos.size(); k++)
  // 		  {
  // 		    b.move(opponent_second_movable_pos[k]);
  // 		    if(b.getMovablePos().size() == 0)
  // 		      {
  // 			// sigenobu revised
  // 			movable_pos.erase(movable_pos.begin() + i);
  // 			b.undo();
  // 			i--;
  // 			erase_flag = true;
  // 			break;
  // 		      }
  // 		    b.undo();
  // 		  }
  // 	      }
  // 	    b.undo();
  // 	    if(erase_flag)
  // 	      break;
  // 	  }
  // 	b.undo();
  //     }

  //   // if you lose whenever you don't use MT, use MT
  //   if(movable_pos.size() == 0)
  //     {
  // 	movable_pos = b.getMovablePos();
  // 	for(int i = 0; i < movable_pos.size(); i++)
  // 	  {
  // 	    // move random
  // 	    int p1 = rand() % movable_pos.size();
  // 	    movable_pos[p1].flag = MTFLAG;
  // 	    b.move(movable_pos[p1]);
  // 	    std::vector<Point> second_movable_pos = b.getMovablePos();
  // 	    // decide coordinates to put coins
  // 	    if(second_movable_pos.size() != 0)
  // 	      {
  // 		int p2 = rand() % second_movable_pos.size();
  // 		second_movable_pos[p2].flag = 0;
  // 		first_point.x  = movable_pos[p1].x;
  // 		first_point.y  = movable_pos[p1].y;
  // 		first_point.flag = MTFLAG;
  // 		second_point.x = second_movable_pos[p2].x;
  // 		second_point.y = second_movable_pos[p2].y;
  // 		first_point.flag = 0;
  // 		return true;
  // 	      }
  // 	    b.undo();
  // 	  }
  // 	return false;
  //     }

  //   // search for a position which you get all coins
  //   for(int i = 0; i < movable_pos.size(); i++)
  //     {
  // 	// first move
  // 	movable_pos[i].flag = MTFLAG;
  // 	b.move(movable_pos[i]);
  // 	// then, get movable position
  // 	std::vector<Point> second_movable_pos = b.getMovablePos();
  // 	// search for a move which you get all discs
  // 	for(int j = 0; j < second_movable_pos.size(); j++)
  // 	  {
  // 	    // second move
  // 	    b.move(second_movable_pos[j]);
  // 	    // judge if you get all discs
  // 	    if(b.getMovablePos().size() == 0)
  // 	      {
  // 		// if you do, return the following data
  // 		first_point.x  = movable_pos[i].x;
  // 		first_point.y  = movable_pos[i].y;
  // 		first_point.flag = MTFLAG;
  // 		second_point.x = second_movable_pos[i].x;
  // 		second_point.y = second_movable_pos[i].y;
  // 		first_point.flag = 0;
  // 		return true;
  // 	      }
  // 	    // if second move isn't suitable, undo the board
  // 	    b.undo();
  // 	  }
  // 	// if first move isn't suitable, undo the board
  // 	b.undo();
  //     }

  //   return false;
  }

