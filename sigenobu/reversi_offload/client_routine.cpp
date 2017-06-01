#include"client_routine.h"
/*! @file

 @brief クライアントの処理機能

 @author 重信 

 @date 作成日 2017.5.23

*/

/*! @brief 初期登録処理
  チーム名をサーバに送り，色の情報を受け取る

 @param[in] teamname チーム名

 @return サーバから受け取った色の情報を返す
 BLACK:0 WHITE:1
*/

int dstSock;

int setting_game(char* teamname){
  char buffer[80];
  Color teamcolor;
  cout << "sending team name...";
  if(send_func(dstSock, teamname)==false){
    cerr << "NG" << endl;
    exit(1);
  }
  cout << "OK" << endl;
  
  cout << "getting my team color...";
  if(recv_func(dstSock, buffer)==false){
    cerr << "NG" << endl;
    exit(1); 
  }
  if(!(strcmp(buffer,"Black"))){
    teamcolor = BLACK;
  }else{
    teamcolor = WHITE;
  }
  cout << "OK" << endl;
  cout << "buffer:" << buffer << endl;
  cout << teamcolor << endl;
  return teamcolor;
}

int board_update(Board &board){
  char c_in[DATASIZE];
  char c_cmp[DATASIZE-1];
  Point p;
  if(recv_func(dstSock, c_in)==false){
    cerr << "move recv miss"<< endl;
    exit(1);
  }
  string in(c_in);
  cout << "in:" << in << endl;
  try
    {
      Point parse(in);
      p = parse;
      cout << "c_in:" << c_in << endl;
    }
      
  //間違った入力
  catch(invalid_argument e)
    {
      cerr <<"wrong input" << endl;
    }
  cout << "p.x:" << p.x << " p.y:" << p.y << endl;
  if(((int)in[FLAGNUM] & ARFLAG) != 0){
    cout << "AC board update" << endl;
    cout << "in[FLAGNAM]:" << (int)in[FLAGNUM] << endl;
    board.Reverse_disk(p, board.getCurrentColor());
    return (int)in[FLAGNUM];

  }else if(((int)in[FLAGNUM] & PSFLAG) != 0){
    cout << "PS board update" << endl;
    cout << "in[FLAGNAM]:" << (int)in[FLAGNUM] << endl;
    board.pass();
    return (int)in[FLAGNUM];

  }else if(p.x == -48 && p.y == 0){
    cout << "board update skip" << endl;
    cout << "in[FLAGNAM]:" << (int)in[FLAGNUM] << endl;
    return (int)in[FLAGNUM];

  }
  if(board.move(p) == false){
    cerr << "board update miss" << endl;
  }
  cout << "in[FLAGNAM]:" << (int)in[FLAGNUM] << endl;
  return (int)in[FLAGNUM];
}

void move_gen(char* move, int x, int y, int flag){
  move[0] = x+'a'-1;
  move[1] = (y/10)+'1'-1;
  move[2] = (y%10)+'1'-1;
  move[3] = flag;
  cout << "move_gen: " << move << endl;
}
