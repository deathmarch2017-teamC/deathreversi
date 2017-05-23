#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#include "GameMaster.h"
#include "Board.h"
#include <string.h>

//wata
#include <string>
#include <unistd.h>
#include <iostream>
#include <GL/freeglut.h> 
#include <GL/glut.h> 
#include <math.h>


//#define M_PI 3.14159265358979 // 円周率
#define PART 36 // 分割数
#define SQUARESIZE 50
#define BLACKSPACE 100
#define WINDOWSIZE 1000
//void draw_circle(int x, int y);

#define PLAYERNUM 2
#define BUFFER_SIZE 256
#define DATASIZE 4//一度にやりとりされるデータの数
#define TIME_LIMIT -1
#define BLACKSOCKET 0
#define WHITESOCKET 1

using namespace std;


int flagforPS =0;
/* ポート番号、ソケット */
char ClientIP[PLAYERNUM][80]={"160.12.172.6","160.12.172.6"};
unsigned short port[PLAYERNUM]={9800,9810};
int dstSocket[PLAYERNUM];  // 相手
int status[PLAYERNUM];

/* sockaddr_in 構造体 */
struct sockaddr_in dstAddr[PLAYERNUM];
int dstAddrSize[PLAYERNUM];
char Teaminfo[20];
char TeamName[PLAYERNUM][40];

/* 各種パラメータ */
int numrcv[PLAYERNUM];
char buffer[BUFFER_SIZE];


void kodama(){

  cout<<"アタックチャーンス!!"<<endl;
  cout<<"　　　／￣￣￣ヽ"<<endl;
  cout<<"　　／／ヾｿ))ﾘ)i＼"<<endl;
  cout<<"　 /\"彡`ヾﾄｿﾂノミ｜"<<endl;
  cout<<"　｜彡　 _ ＿　 ﾐ｜"<<endl;
  cout<<"　 ﾚ彡 ＿_　 ＿ヽ/"<<endl;
  cout<<"　(6ｲ　ィo、 ｨo､∥"<<endl;
  cout<<"　ヽ|　､＿ﾉ i､_ ｜"<<endl;
  cout<<"　 ｜＿　r､_ｂヽ/"<<endl;
  cout<<"＿／r三ﾐDー-→ソ"<<endl;  
  cout<<"　|｜^ rj ＿\"ノ-、"<<endl;
  cout<<"　`ﾉ　 )ヽ_/|＼　ヽ"<<endl;
  cout<<"　∧ _∧ /ヽ|　ヽ |"<<endl;
  sleep(3);
}

void colombia(string answer){


  cout<<"　 　 　 　　　　　　　 　　　　　　　　　　 　　　 ,.へ"<<endl;
  cout<<"　　___ 　　　　　　　 　 　 　 　　　　　 　　　　ﾑ　　i"<<endl;
  cout<<"「 ﾋ_i〉　　　 　 　　　　　　 　　　　　　 　　　 ゝ　〈"<<endl;
  cout<<"ﾄ　ノ 　　　　　　　　　　　　　　　　　　　 　　　iニ(()"<<endl;
  cout<<"i 　{ 　 　　　　　　　 　　　＿＿＿_ 　 　　　　　| 　ヽ"<<endl;
  cout<<"i　　i　　　 　　　　　 　／__,　 , ‐-＼  　  　 　i  　}"<<endl;
  cout<<"|　　 i　　　　　　 　　／（●) 　 ( ● ) ＼　　　   {､　 λ"<<endl;
  cout<<"　ト－┤.　　　　　  　／ 　 （__人__）  　＼　　 ,ノ　￣,!"<<endl;
  cout<<"　i　　　ゝ､_ 　　　　|　　　  ´￣` 　 　 　|　,. '´ﾊ　,!"<<endl;
  cout<<".　ヽ、 　　　｀`　､,__＼ 　　 　 　　　　 ／\"　＼ 　／"<<endl;
  cout<<"　　　＼ノ　ﾉ　　　ﾊ￣r/:::r―--―/::７　　 ﾉ　　   ／"<<endl;
  cout<<"　 　　 ヽ_　　　　　　ヽ::〈'::. :'|::/        /　　　,."<<endl;
  cout<<"　         `ｰ ､　     ＼ヽ::. ;::：|/　  　ｒ'\""<<endl;
  cout<<"　　　　　／￣二二二二二二二二二二二二二二二二ヽ"<<endl;
  cout<<"          | 答 |           "<<answer<<"                │|"<<endl;
  cout<<"　　　　　＼＿二二二二二二二二二二二二二二二二ノ"<<endl;
  cout<<""<<endl;
  cout<<""<<endl;
  sleep(3);
}




ostream& operator<<(ostream& os, const Point& p)
{
	string s = p;
	os << s;
	return os;
}

void assign_stringtochar(string input, char *output){
  for(int i=0;i<DATASIZE;i++){
    output[i]=input[i];
  }
}

void assign_chartostring(char *input, string &output){
  for(int i=0;i<DATASIZE;i++){
    output[i]=input[i];
  }
}

void assign_char(char *input, char *output){
  for(int i=0;i<DATASIZE;i++){
    output[i]=input[i];
  }
}


void GFprocess(ConsoleBoard &board){      
  glRasterPos2d(50, 50);//0,0,0位置をスタート位置にする

  if(board.countDisc(BLACK)>board.countDisc(WHITE)){
    cout<<"WINER is BLACK"<<endl;
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)("BLACK WIN"));
    
  }
  else if(board.countDisc(BLACK)<board.countDisc(WHITE)){
    cout<<"WINER is WHITE"<<endl;   
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)("WHITE WIN"));
    
  }
  else{
    cout<<"DRAW"<<endl;
  }
  cout << "----------------Game Finish----------------" << endl;
  glutSwapBuffers();

  //**********************通信ポイント*******************
  char send_data[DATASIZE];
  send_data[0]='0';
  send_data[1]='0';
  send_data[2]='0';
  send_data[3]=GFFLAG;
  
  send(dstSocket[BLACKSOCKET], send_data,strlen(send_data)+1,0);
  send(dstSocket[WHITESOCKET], send_data,strlen(send_data)+1,0);
  
  sleep(50);
  exit(0);
}

void time_out(Color current_color){

  string in;
  glRasterPos2d(50, 50);//0,0,0位置をスタート位置にする
 
  if(current_color == BLACK){
    cout  << "time out" <<endl;
    cout << "LOSER is BLACK "<<endl;
    cout << "please input any character and push Enter key"<<endl;
     glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)("BLACK LOSER"));
     glutSwapBuffers();
    cin>>in;
  }
  else{
    cout  << " time out" <<endl;
    cout << "LOSER is WHITE"<<endl;
    cout << "please input any character and push Enter key"<<endl;
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)("WHITE LOSER"));
    glutSwapBuffers();
    cin>>in;
  }
  //**********************通信ポイント*******************
  char send_data[DATASIZE];
  send_data[0]='0';
  send_data[1]='0';
  send_data[2]='0';
  send_data[3]=GFFLAG;
  
  send(dstSocket[BLACKSOCKET], send_data,strlen(send_data)+1,0);
  send(dstSocket[WHITESOCKET], send_data,strlen(send_data)+1,0);
  exit(0);
}

void draw_circle(int xpos, int ypos, Color color){
 
  int r = 0.5;
  float x,y, rate;
  //座標変換
  xpos = xpos * SQUARESIZE + BLACKSPACE -(SQUARESIZE/2);  
  ypos = ypos * SQUARESIZE + BLACKSPACE -(SQUARESIZE/2);
  if(color == WHITE){
    glColor3f(1,1,1);
  }else{
    glColor3f(0,0,0);
  }
  glBegin(GL_POLYGON); // ポリゴンの描画
  // 円を描画
  for (int i = 0; i < PART; i++) {
    // 座標を計算
    rate = (double)i / PART;
    x = (SQUARESIZE/2) * cos(2.0 * M_PI * rate);
    y = (SQUARESIZE/2) * sin(2.0 * M_PI * rate);
    glVertex2f(x+xpos, y+ypos); // 頂点座標を指定
  }
  glEnd();
}

void draw_board(Board board){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //ラインを描く
  glColor3f(0,0,0);
  glLineWidth(3);//線幅の指定。省略可。指定しなければ1。
  glBegin(GL_LINES);
  for(int i=0;i<13;i++){
    glVertex2i(BLACKSPACE + SQUARESIZE*i,700);//
    glVertex2i(BLACKSPACE + SQUARESIZE*i,BLACKSPACE);//
    glVertex2i(BLACKSPACE, BLACKSPACE+SQUARESIZE*i);//
    glVertex2i(700,BLACKSPACE + SQUARESIZE*i);//
  }
  glEnd();
  
  //点を5箇所描く
  glColor3f(0,0,0);
  glPointSize(10);
  glBegin(GL_POINTS);
  glVertex2i(250,250);
  glVertex2i(250,550);
  glVertex2i(550,250);
  glVertex2i(550,550);
  glVertex2i(400,400);
  glEnd();
  
  //4隅を壁に クロしかく
  glBegin(GL_POLYGON);
  glVertex2i(700, 700);
  glVertex2i(650, 700);
  glVertex2i(650, 650);
  glVertex2i(700, 650);
  glEnd();
  
  glBegin(GL_POLYGON);
  glVertex2i(100, 100);
  glVertex2i(100, 150);
  glVertex2i(150, 150);
  glVertex2i(150, 100);
  glEnd();
  
  glBegin(GL_POLYGON);
  glVertex2i(100, 650);
  glVertex2i(100, 700);
  glVertex2i(150, 700);
  glVertex2i(150, 650);
  glEnd();
  
  glBegin(GL_POLYGON);
  glVertex2i(650, 100);
  glVertex2i(650, 150);
  glVertex2i(700, 150);
  glVertex2i(700, 100);
  glEnd();
  ////////////////////

  //マスの番号/////////////////////////////////////////////////////////////
  glRasterPos2d(125,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("a"));

  glRasterPos2d(175,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("b"));

  glRasterPos2d(225,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("c"));

  glRasterPos2d(275,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("d"));

  glRasterPos2d(325,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("e"));

  glRasterPos2d(375,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("f"));

  glRasterPos2d(425,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("g"));

  glRasterPos2d(475,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("h"));

  glRasterPos2d(525,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("i"));

  glRasterPos2d(575,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("j"));

  glRasterPos2d(625,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("k"));

  glRasterPos2d(675,80);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("l"));

  glRasterPos2d(70,130);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("01"));

  glRasterPos2d(70,180);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("02"));

  glRasterPos2d(70,230);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("03"));

  glRasterPos2d(70,280);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("04"));

  glRasterPos2d(70,330);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("05"));

  glRasterPos2d(70,380);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("06"));

  glRasterPos2d(70,430);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("07"));

  glRasterPos2d(70,480);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("08"));

  glRasterPos2d(70,530);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("09"));

  glRasterPos2d(70,580);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("10"));

  glRasterPos2d(70,630);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("11"));
  
  glRasterPos2d(70,680);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)("12"));
  //////////////////////////////////////////////////////////////////////////
    
  
  // 石を描画
  for(int y=1; y<=BOARD_SIZE; y++){
    for(int x=1; x<=BOARD_SIZE; x++){
      switch(board.getColor(Point(x, y)))
	{
	case BLACK:
	  draw_circle(x,y,BLACK);
	  break;
	case WHITE:
       	  draw_circle(x,y,WHITE);
	  break;
	default:
	  break;
	}
    }
  }
}


void against_rules(Color current_color){

  string in;

  if(current_color == BLACK){
    cout  << "you against the rule" <<endl;
    cout << "LOSER is BLACK "<<endl;
    cout << "please input any character and push Enter key"<<endl;
    cin>>in;
  }
  else{
    cout  << "you against the rule" <<endl;
    cout << "LOSER is WHITE"<<endl;
    cout << "please input any character and push Enter key"<<endl;
    cin>>in;
  }
  //**********************通信ポイント*******************
  //client は勝手に終了?
  char send_data[DATASIZE];
  send_data[0]='0';
  send_data[1]='0';
  send_data[2]='0';
  send_data[3]=GFFLAG;
  
  send(dstSocket[BLACKSOCKET], send_data,strlen(send_data)+1,0);
  send(dstSocket[WHITESOCKET], send_data,strlen(send_data)+1,0);
  exit(0);
}

bool attack_chance(int current_color, ConsoleBoard &board, string premove){

  if(current_color == BLACK){
    cout << "So, Black, What number?"<<endl;

  }
  else{
    cout << "So, White, What number?"<<endl;
  }


  string in(DATASIZE,0);
  char buffer[BUFFER_SIZE];
  char send_data[DATASIZE];



  //**********************通信ポイント*******************

  premove[3] = ACFLAG;
  if(flagforPS ==true){
    premove[3]= premove[3] | PSFLAG;
  }
  assign_stringtochar(premove, send_data);
  if(current_color==BLACK){
    if(TIME_LIMIT == send(dstSocket[BLACKSOCKET], send_data,strlen(send_data)+1,0)) time_out(current_color);
    if(TIME_LIMIT == recv(dstSocket[BLACKSOCKET], buffer, BUFFER_SIZE, 0)) time_out(current_color);
  }else{
     if(TIME_LIMIT == send(dstSocket[WHITESOCKET], send_data,strlen(send_data)+1,0)) time_out(current_color);
     if(TIME_LIMIT == recv(dstSocket[WHITESOCKET], buffer, BUFFER_SIZE, 0)) time_out(current_color);
  }
  assign_chartostring(buffer, in);
  cout<<"revese Disk:"<<in<<endl;
  //****************************************************


  //debug
  //cout<<"char to string buffer0"<<buffer<<endl;
  //cout<<"char to string buffer1"<<buffer<<endl;
  //cout<<"char to string buffer2"<<buffer<<endl;
  //cout<<"char to string buffer3"<<hex<<(int)buffer<<endl;
  
  Point p(in);

  //もし指定ますに相手の石がなかったら
  if(board.getColor(p) != (-current_color)){
    cout<<"Against the rules"<<endl;
    against_rules(current_color);
    }
  else{//相手の石があったら
    colombia(in);
    board.Reverse_disk(p, current_color);
    assign_char(buffer, send_data);
    send_data[3]=ARFLAG;
    //**********************通信ポイント*******************
    if(current_color==BLACK){
      if(TIME_LIMIT == send(dstSocket[WHITESOCKET], send_data,strlen(send_data)+1,0)) time_out(current_color);
    }else{
      if(TIME_LIMIT == send(dstSocket[BLACKSOCKET], send_data,strlen(send_data)+1,0)) time_out(current_color);
    }
    //****************************************************************
  }
  if(board.isGameOver()){
    board.print();
    draw_board(board);
    glutSwapBuffers();
    
    cout << "Black Disk:" << board.countDisc(BLACK) << " ";
    cout << "White Disk:" << board.countDisc(WHITE) << " ";
    cout << "Empty:" << board.countDisc(EMPTY) << endl;
    GFprocess(board);
  }
  return true;
}





void display(void)
{	
    for(int i=0;i<PLAYERNUM;i++){
    dstAddrSize[i]  = sizeof(dstAddr);
  }

  /************************************************************/
  /* 相手先アドレスの入力 */
 
  
  cout<<"BLACK IP address :";
  cin>>ClientIP[BLACKSOCKET];

  cout<<"BLACK port :";
  cin>>port[BLACKSOCKET];

  cout<<"WHITE IP adrress :";
  cin>>ClientIP[WHITESOCKET];
  
  cout<<"WHITE port :";
  cin>>port[WHITESOCKET];

  /************************************************************/
  for(int i=0;i<PLAYERNUM;i++){
    /* sockaddr_in 構造体のセット */
    memset(&dstAddr[i], 0, sizeof(dstAddr));
    dstAddr[i].sin_port = htons(port[i]);
    dstAddr[i].sin_family = AF_INET;
    dstAddr[i].sin_addr.s_addr = htonl(INADDR_ANY);
    
    /* ソケットの生成 */
    dstSocket[i] = socket(AF_INET, SOCK_STREAM, 0);

    /* ソケットのバインド */
    bind(dstSocket[i], (struct sockaddr *) &dstAddr[i], sizeof(dstAddr[i]));

    /* 接続の許可 */
    listen(dstSocket[i], 1);

    /* 接続の受付け */
    printf("Waiting for connection ...\n");
    dstSocket[i] = accept(dstSocket[i], (struct sockaddr *) &dstAddr[i], &dstAddrSize[i]);
    printf("Connected from %s\n", inet_ntoa(dstAddr[i].sin_addr));

    /* パケット受信 */
    numrcv[i] = recv(dstSocket[i], buffer, BUFFER_SIZE, 0); 
    cout<<"received:"<<buffer<<endl;
    
    if(i==0){
      strcpy(Teaminfo,"Black");
      //名前登録処理
      strcpy(TeamName[i],buffer);
      cout<<"Black's Team name : "<<TeamName[i]<<endl; 
    }else {
      strcpy(Teaminfo,"White");
      //名前登録処理
      strcpy(TeamName[i],buffer);
      cout<<"White's Team name : "<<TeamName[i]<<endl;
    }

    send(dstSocket[i], Teaminfo,strlen(Teaminfo)+1, 0);
  }


  /*ゲームスタート*/
  ConsoleBoard board;
  string premove(DATASIZE,0);
  premove[0]='0';
  premove[1]='0';
  premove[2]='0';
  premove[3] = 0;
  int attack_cahnce_status=false;
  int mt_status_BLACK=false;
  int mt_status_WHITE=false;
  
  //制限時間
  struct timeval limit_tv;
  limit_tv.tv_sec  = 1;//sec
  limit_tv.tv_usec = 0;//usec
  
  //ソケットのタイムアウト設定
  for(int i=0;i<PLAYERNUM;i++){
    setsockopt(dstSocket[i], SOL_SOCKET, SO_SNDTIMEO, (char *)&limit_tv, sizeof(limit_tv));
  }

  while(true){

      board.print();
      draw_board(board);
      glutSwapBuffers();
    
      cout << "Black Disk:" << board.countDisc(BLACK) << " ";
      cout << "White Disk:" << board.countDisc(WHITE) << " ";
      cout << "Empty:" << board.countDisc(EMPTY) << endl;
		
      int current_color =  board.getCurrentColor();
      if(current_color == BLACK){
	cout<<"Black Turn("<<TeamName[BLACKSOCKET]<<")"<<endl; 
      }
      else{
	cout<<"White Turn("<<TeamName[WHITESOCKET]<<")"<<endl;
      }
  
		
      cout << endl << endl;

      //特殊ルールの追加 attack cance
      //残りますが10以下 かつ 20石以上負けている アタックチャンスが起こっていない
      if( (board.countDisc(EMPTY) <= 10) && ( (board.countDisc(-current_color)-board.countDisc(current_color) ) >= ATTACKNUM) && (attack_cahnce_status == false ) ){
	kodama();
	attack_cahnce_status = true;
	attack_chance(current_color, board, premove);
	
	board.print();
	draw_board(board);
	glutSwapBuffers();
    
	cout << "Black Disk:" << board.countDisc(BLACK) << " ";
	cout << "White Disk:" << board.countDisc(WHITE) << " ";
	cout << "Empty:" << board.countDisc(EMPTY) << endl;
	
	if(current_color == BLACK){
	  cout<<"Black Turn"<<endl; 
	}
	else{
	  cout<<"White Turn"<<endl;
	}
	premove[0]='0';
	premove[1]='0';
	premove[2]='0';
	}
      
	cout << "input your move: ";
	Point p;
	
	string in(DATASIZE,0);

	//**********************通信ポイント*******************
	//send data to player and recieve data from player
	premove[3] = 0;
	if(flagforPS == true)  premove[3] = premove[3] | PSFLAG;
	char send_data[DATASIZE];
	assign_stringtochar(premove, send_data);
	if(current_color == BLACK){
	  if(TIME_LIMIT == send(dstSocket[BLACKSOCKET], send_data,strlen(send_data)+1,0)) time_out(current_color);
	  if(TIME_LIMIT == recv(dstSocket[BLACKSOCKET], buffer, BUFFER_SIZE,0)) time_out(current_color);
	}else {
	  if(TIME_LIMIT ==  send(dstSocket[WHITESOCKET], send_data,strlen(send_data)+1,0)) time_out(current_color);
	  if(TIME_LIMIT ==  recv(dstSocket[WHITESOCKET], buffer, BUFFER_SIZE, 0)) time_out(current_color);
	} 
	flagforPS  = false;
	assign_chartostring(buffer, in);
	cout<<in<<endl;
	cout<<"in0"<<in[0]<<endl;
	cout<<"in1"<<in[1]<<endl;
	cout<<"in2"<<in[2]<<endl;
	cout<<"in3"<<hex<<in[3]<<endl;
      /**********************************************************/
      

	//手判断
	//パスなら
      if(in[0] == 'p')
	{
	  // パス
	  if(!board.pass()){
	    cerr << "you can't pass " << endl;
	    against_rules(current_color);
	  }else {
	    cout<<"PASS"<<endl;
	    flagforPS= true;
	    premove[0]='0';
	    premove[1]='0';
	    premove[2]='0';   
	  }
	  if(board.isGameOver())
	    { board.print();
	      draw_board(board);
	      glutSwapBuffers();
    
	      cout << "Black Disk:" << board.countDisc(BLACK) << " ";
	      cout << "White Disk:" << board.countDisc(WHITE) << " ";
	      cout << "Empty:" << board.countDisc(EMPTY) << endl;
	      GFprocess(board);
	      break;
	    }
	  
	  continue;
	}
	
      //point に変換
      try
	{
	  Point parse(in);
	  p = parse;
	}
      
      //間違った入力
      catch(invalid_argument e)
	{
	  cerr <<"wrong your input" << endl;
	  against_rules(current_color);
	  continue;
	}
      
      //おけない場所
      if(board.move(p) == false)
	{
	  cerr << "you can't move the place" << endl;
	  against_rules(current_color);
	  continue;
	}
    
      premove = in;


      //test mtflag
      if((p.flag & MTFLAG) == MTFLAG){
	if( (current_color == WHITE) && (mt_status_WHITE == true)){//もしMTFLAGが同じプレイヤーで二度あったら違反 flagによりcurrentcolorはそのままでよい
	  against_rules(current_color);
	}
	else if( (current_color == BLACK) && (mt_status_BLACK == true)){
	  against_rules(current_color);
	}
	else if(board.getTurns()<10){
	  against_rules(current_color);	  
	}
	cout<<"Still my turn!!!!!!!!!"<<endl;
      
	if(current_color==WHITE){
	  mt_status_WHITE=true;
	}
	else{
	  mt_status_BLACK=true;
	}
	premove[3]= MTFLAG;
	//mtかつps
	if(flagforPS == true){
	  premove[3]=MTFLAG | PSFLAG;
	}

     	//**********************通信ポイント*******************
	char send_data[DATASIZE];
	assign_stringtochar(premove, send_data);
	if(current_color==BLACK){
	  if(TIME_LIMIT == send(dstSocket[WHITESOCKET], send_data,strlen(send_data)+1,0)) time_out(current_color);
	}else{
	  if(TIME_LIMIT == send(dstSocket[BLACKSOCKET], send_data,strlen(send_data)+1,0)) time_out(current_color);
	}
	premove[0]='0';
	premove[1]='0';
	premove[2]='0';
      	premove[3]=0;
	continue;
      }
      

      if(board.isGameOver())
	{
	  board.print();
	  draw_board(board);
	  glutSwapBuffers();
    
	  cout << "Black Disk:" << board.countDisc(BLACK) << " ";
	  cout << "White Disk:" << board.countDisc(WHITE) << " ";
	  cout << "Empty:" << board.countDisc(EMPTY) << endl;
	  GFprocess(board);
	  break;
	}
    }
 
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);	
	glutInitWindowSize(WINDOWSIZE, WINDOWSIZE);//ウィンドウの画面の幅と高さを指定
	glutInitWindowPosition(0, 0);//ウィンドウの場所を指定
	glutCreateWindow("reversi");//ウィンドウの名前
	glClearColor( 0 , 0.7, 0, 1);//オセロ盤の色
	gluOrtho2D(0, 800, 800,0);//座標系の設定
	glutDisplayFunc(display);//描画関数を指定
	glutMainLoop();
	cout<<"hogehoge"<<endl; 
	return 0;
}
