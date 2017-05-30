#include"client_routine.h"

int main(){
  char teamname[]={"teamC"};
  char ip_addr[80];
  int port;
  int teamcolor;
  char moveout[4];
  ConsoleBoard board;
  Reversi_AI_ab AI;
  int x_out;
  int y_out;
  int flagout;
  int flagin;
  Point mymove;
  
  cout << "server IP address:";
  cin >> ip_addr;
  cout << "server port:";
  cin >> port;
  
  if(set_socket(ip_addr, port)==false){
    cerr << "connection miss" << endl;
  }

  printf("start setting_game\n");
  if((teamcolor = setting_game(teamname)) == BLACK){
    printf("my color is BLACK!\n");
  }else{
    printf("my color is WHITE!\n");
  }
  printf("end initial setting\n");
  
  while(true){
    cout << "Turn:" << board.getTurns() << endl;
    if((board.getTurns() != 0) || teamcolor == WHITE){
      flagin = board_update(board);
      board.print();
      cout << "Black Disk:" << board.countDisc(BLACK) << endl;
      cout << "White Disk:" << board.countDisc(WHITE) << endl;
      cout << "Empty:" << board.countDisc(EMPTY) << endl << endl;
    }else{
      recv_func(moveout);
      flagin = 0;
    }
    if((flagin & MTFLAG) != 0 ){
      cout << "receive MT" << endl;
     
    }else if((flagin & ARFLAG) != 0 ){
      cout << "receive AR" << endl;

    }else if((flagin & ACFLAG) != 0 ){
      cout << "receive AC" << endl;
      AI.return_move(board, flagin, x_out, y_out, flagout);
     
      Point ACdisk(x_out, y_out, flagout);

      board.Reverse_disk(ACdisk, board.getCurrentColor());
      
      move_gen(moveout, x_out, y_out, flagout);
      cout << "move:" << moveout << " flag:" << flagout << endl;

      send_func(moveout);
      
      /* }else if((flagin & PSFLAG) != 0 ){
	 cout << "receive PS" << endl;
	 if(board.pass()==false){
	 cerr << "miss Pass routine\n" << endl;
	 AI.return_move(board, flagin, x_out, y_out, flagout);

	 move_gen(moveout, x_out, y_out, flagout);
	 cout << "move:" << moveout << " flag:" << flagout << endl << endl;

	 send_func(moveout);

	 }*/
    }else if((flagin & GFFLAG) != 0 ){
      cout << "game set!" << endl;
      break;
    }else{
      AI.return_move(board, flagin, x_out, y_out, flagout);

      if(flagout == PSFLAG){
	board.pass();
	moveout[0] = 'p';
	moveout[1] = '0';
 	moveout[2] = '0';
	moveout[3] = '0';

	cout << "******************** PASS ********************" << endl;

	cout << "move:" << moveout << " flag:" << flagout << endl << endl;

	send_func(moveout);

      }else{
      
	Point mymove(x_out, y_out, flagout);
      
	if(board.move(mymove)==false){
	  cerr << "board update(mymove) miss" << endl;
	}
      
	board.print();
	cout << "Black Disk:" << board.countDisc(BLACK) << endl;
	cout << "White Disk:" << board.countDisc(WHITE) << endl;
	cout << "Empty:" << board.countDisc(EMPTY) << endl;
      
	move_gen(moveout, x_out, y_out, flagout);

	cout << "move:" << moveout << " flag:" << flagout << endl << endl;

	send_func(moveout);
      }
    }
  }

  if(close_socket()<0){
    cerr << "close serverSock miss" << endl;
  }else{
    cout << "serverSock closed !" << endl;
  }
  return 0;
}
