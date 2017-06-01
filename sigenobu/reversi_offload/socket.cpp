#include"socket.h"
#define BUFFER_SIZE 256
#define MTFLAG  0b00000001//まだまだ俺のターン
#define ACFLAG  0b00000010//アタックチャンス使用側
#define ARFLAG  0b00000100//アタックチャンス受ける側
#define PSFLAG  0b00001000//パスフラグ
#define GFFLAG  0b00010000//ゲーム終了
#define FLAGNUM 3//文字列の何個目がフラグのbitか 0から数える


int set_socket_connect(char* ip_addr, int port){
  struct sockaddr_in dstSockaddr;
  int dstSock;

  //ソケットの生成
  dstSock = socket(AF_INET, SOCK_STREAM, 0);

  //接続先構造体の準備
  dstSockaddr.sin_family = AF_INET;
  dstSockaddr.sin_port = htons(port);

  inet_pton(AF_INET, ip_addr,  &dstSockaddr.sin_addr.s_addr);

  //サーバに接続
  if(connect(dstSock, (struct sockaddr *) &dstSockaddr, (socklen_t)sizeof(dstSockaddr))<-1){
    //perror("connect error\n");
    return 0;
  }
  
  return dstSock;
}

int set_socket_accept(int port){
  int dstSock;
  struct sockaddr_in dstSockaddr;
    dstSockaddr.sin_port = htons(port);
    dstSockaddr.sin_family = AF_INET;
    dstSockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    dstSock = socket(AF_INET, SOCK_STREAM, 0);
    
    bind(dstSock, (struct sockaddr *) &dstSockaddr, sizeof(dstSockaddr));

    listen(dstSock, 1);
    std::cout << "wait connection ..." << std::endl;
    if(dstSock = accept(dstSock, (struct sockaddr *) &dstSockaddr, (socklen_t *)sizeof(dstSockaddr)) < -1){
      std::cout << "not connect" << std::endl;
      return 0;
    }
    printf("connected %s\n", inet_ntoa(dstSockaddr.sin_addr));
    return dstSock;
}

//送信する関数
bool send_func(int socket ,char* buf){

  //送信
  if(send(socket, buf, strlen(buf)+1,0)<0){
    //perror("send error\n");
    return false;
  }

  return true;
}

//受信する関数
bool recv_func(int socket, char* buf){
  //サーバからデータを受信
  //memset(buf, 0, sizeof(buf));
  if(recv(socket, buf, BUFFER_SIZE,0)<0){
    perror("recv error\n");
    return false;
  }

  return true;
}

int close_socket(int socket){
  return close(socket);
}
