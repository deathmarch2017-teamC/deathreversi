#include"socket.h"
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
char move[4];
char buffer[BUFFER_SIZE];

int main()
{
  dstSocket[OFFLOAD] = set_socket_connect(ip_addr[OFFLOAD], port[OFFLOAD]);
  if(recv_func(dstSocket[OFFLOAD], buffer) == false){
    cout << "team name recv miss" << endl;
  }


  cout << "server IP address:";
  cin >> ip_addr[SERVER];
  cout << "server port:";
  cin >> port[SERVER];
  
  dstSocket[SERVER] = set_socket_connect(ip_addr[SERVER], port[SERVER]);
  
  if(send_func(dstSocket[SERVER], buffer) == false){
    cout << "team name send miss" << endl;
  }

  while(true){
    if(recv_func(dstSocket[SERVER], move) == false){
      cout << "move recv miss" << endl;
    }
    
    if(move[FLAGNUM] && MTFLAG){
      if(send_func(dstSocket[OFFLOAD], move) == false){
	cout << "MT move send to OFFLOAD miss" << endl;
      }
      continue;
      
    }else if(move[FLAGNUM] && ARFLAG){
      if(send_func(dstSocket[OFFLOAD], move) == false){
	cout << "AR move send to OFFLOAD miss" << endl;
      }
      continue;
      
    }else if(move[FLAGNUM] && GFFLAG){
      if(send_func(dstSocket[OFFLOAD], move) == false){
	cout << "GF move send to OFFLOAD miss" << endl;
      }
      break;

      
    }else{
      if(send_func(dstSocket[OFFLOAD], move) == false){
	cout << "move send to OFFLOAD miss" << endl;
      }
      
      if(recv_func(dstSocket[OFFLOAD], move) == false){
	cout << "move recv to OFFLOAD miss" << endl;
      }

      if(send_func(dstSocket[SERVER], move) == false){
	cout << "move send to SERVER miss" << endl;
      }

      
    }
  }
  close_socket(dstSocket[OFFLOAD]);
  close_socket(dstSocket[SERVER]);
 
}
