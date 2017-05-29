#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 12345


//送信する関数
int send_func(char* BUF){

  //  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  int len;
  int sock;

  //ソケットの作成
  sock = socket(AF_INET, SOCK_STREAM, 0);

  //ソケットの設定
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(sock, (struct sockaddr *) &addr, sizeof(addr));

  //TCPクライアントから接続要求を待機
  listen(sock, 1);

  //TCPクライアントから接続要求を受ける
  len = sizeof(client);
  sock = accept(sock, (struct sockaddr *) &client, (socklen_t*)&len);

  //送信
  send(sock,BUF, 4,0);

  //TCPセッション終了
  close(sock);

  //listen するSocketの終了
  // close(sock0);
}

int main(){
  char BUF[4]={"SEN"};
  send_func(BUF);
  return 0;
}
