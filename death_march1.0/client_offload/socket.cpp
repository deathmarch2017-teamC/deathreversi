#include"socket.h"
#include<errno.h>
#define BUFFER_SIZE 256

// bool set_socket_connect(char* ip_addr, int port){
//   struct sockaddr_in dstSockaddr;

//   //ソケットの生成
//   dstSock = socket(AF_INET, SOCK_STREAM, 0);

//   //接続先構造体の準備
//   dstSockaddr.sin_family = AF_INET;
//   dstSockaddr.sin_port = htons(port);

//   inet_pton(AF_INET, ip_addr, &dstSockaddr.sin_addr.s_addr);

//   //サーバに接続
//   if(connect(dstSock, (struct sockaddr *) &dstSockaddr, (socklen_t)sizeof(dstSockaddr))<-1){
//     //perror("connect error\n");
//     return false;
//   }
  
//   return true;
// }

int dstSock;

bool set_socket_accept(char* ip_addr, int port){
struct sockaddr_in dstSockaddr;

  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  int len;

  //ソケットの作成
  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  //ソケットの設定
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(sock0, (struct sockaddr *) &addr, sizeof(addr));

  //TCPクライアントから接続要求を待機
  listen(sock0, 5);

  //TCPクライアントから接続要求を受ける
  printf("wait accept...\n");
  len = sizeof(client);
  dstSock = accept(sock0, (struct sockaddr *) &client, (socklen_t *)&len);

  printf("accept complete!\n");
  return true;
}

//送信する関数
bool send_func(char* buf){

  //送信
  if(send(dstSock, buf, strlen(buf)+1,0)<0){
    perror("send error\n");
    return false;
  }

  return true;
}

//受信する関数
bool recv_func(char* buf){
  //サーバからデータを受信
  //memset(buf, 0, sizeof(buf));
  if(recv(dstSock, buf, BUFFER_SIZE,0)<0){
    perror("recv error\n");
    return false;
  }

  return true;
}

int close_socket(){
  return close(dstSock);
}
