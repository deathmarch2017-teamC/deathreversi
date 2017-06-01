#include"raspi_socket.h"
#define BUFFER_SIZE 256
#define OFFLOAD 0
#define SERVER 1
#define MTFLAG  0b00000001//まだまだ俺のターン
#define ACFLAG  0b00000010//アタックチャンス使用側
#define ARFLAG  0b00000100//アタックチャンス受ける側
#define PSFLAG  0b00001000//パスフラグ
#define GFFLAG  0b00010000//ゲーム終了
#define FLAGNUM 3//文字列の何個目がフラグのbitか 0から数える

using namespace std;

int serverSock[2];
char ip_addr[2][80]={"160.12.172.6","160.12.172.91"};
int port[2] = {30000,10000};
int dstSocket[2];
struct sockaddr_in dstSockaddr[2];
char move[4];
char buffer[BUFFER_SIZE];

int main()
{
  //ソケットの生成
  dstSocket[OFFLOAD] = socket(AF_INET, SOCK_STREAM, 0);

  //接続先構造体の準備
  dstSockaddr[OFFLOAD].sin_family = AF_INET;
  dstSockaddr[OFFLOAD].sin_port = htons(port[OFFLOAD]);

  inet_pton(AF_INET, ip_addr[OFFLOAD], &dstSockaddr[OFFLOAD].sin_addr.s_addr);

  //サーバに接続
  if(connect(dstSocket[OFFLOAD], (struct sockaddr *) &dstSockaddr, (socklen_t)sizeof(dstSockaddr))<-1){
    cout << "connect offload miss" << endl;
  }
  cout << "connect to offload PC !" << endl;

  if(recv_raspi_off(buffer) == false){
    cout << "team name recv miss" << endl;
  }
  cout << "team name recv:" << buffer << endl;


  cout << "server IP address:";
  cin >> ip_addr[SERVER];
  cout << "server port:";
  cin >> port[SERVER];
  
  //ソケットの生成
  dstSocket[SERVER] = socket(AF_INET, SOCK_STREAM, 0);

  //接続先構造体の準備
  dstSockaddr[SERVER].sin_family = AF_INET;
  dstSockaddr[SERVER].sin_port = htons(port[SERVER]);

  inet_pton(AF_INET, ip_addr[SERVER], &dstSockaddr[SERVER].sin_addr.s_addr);

  //サーバに接続
  if(connect(dstSocket[SERVER], (struct sockaddr *) &dstSockaddr, (socklen_t)sizeof(dstSockaddr))<-1){
    cout << "connect server miss" << endl;
  }
  cout << "connect to server PC !" << endl;


  if(send_raspi_server(buffer) == false){
    cout << "team name send miss" << endl;
  }
  cout << "team name send:" << buffer << endl;

  while(true){
    if(recv_raspi_server(move) == false){
      cout << "move recv (server) miss" << endl;
    }
    cout << "move recv (server):" << move << endl;
    
    if(move[FLAGNUM] && MTFLAG){
      if(send_raspi_off(move) == false){
	cout << "MT move send to OFFLOAD miss" << endl;
      }
      cout << "MT move send (offload):" << move << endl;

      continue;
      
    }else if(move[FLAGNUM] && ARFLAG){
      if(send_raspi_off(move) == false){
	cout << "AR move send to OFFLOAD miss" << endl;
      }
      cout << "AR move send (offload):" << move << endl;
      
      continue;
      
    }else if(move[FLAGNUM] && GFFLAG){
      if(send_raspi_off(move) == false){
	cout << "GF move send to OFFLOAD miss" << endl;
      }
      cout << "GF move send (offload):" << move << endl;

      break;

      
    }else{
      if(send_raspi_off(move) == false){
	cout << "move send to OFFLOAD miss" << endl;
      }
      cout << "move send (offload):" << move << endl;

      
      if(recv_raspi_off(move) == false){
	cout << "move recv to OFFLOAD miss" << endl;
      }
      cout << "move recv (offload):" << move << endl;

      if(send_raspi_server(move) == false){
	cout << "move send to SERVER miss" << endl;
      }
      cout << "move send (server):" << move << endl;

      
    }
  }
  close(dstSocket[OFFLOAD]);
  close(dstSocket[SERVER]);
 
}

bool send_raspi_off(char* buf){

  //送信
  if(send(dstSocket[OFFLOAD], buf, strlen(buf)+1,0)<0){
    perror("send error\n");
    return false;
  }

  return true;
}

//受信する関数
bool recv_raspi_off(char* buf){
  //サーバからデータを受信
  //memset(buf, 0, sizeof(buf));
  if(recv(dstSocket[OFFLOAD], buf, BUFFER_SIZE,0)<0){
    perror("recv error\n");
    return false;
  }

  return true;
}
bool send_raspi_server(char* buf){

  //送信
  if(send(dstSocket[SERVER], buf, strlen(buf)+1,0)<0){
    perror("send error\n");
    return false;
  }

  return true;
}

//受信する関数
bool recv_raspi_server(char* buf){
  //サーバからデータを受信
  //memset(buf, 0, sizeof(buf));
  if(recv(dstSocket[SERVER], buf, BUFFER_SIZE,0)<0){
    perror("recv error\n");
    return false;
  }

  return true;
}
