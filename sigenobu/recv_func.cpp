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


#include <string>

#define PORT 12345

//受信する関数
char recv_func(char buf[5]){
  struct sockaddr_in server;
  int sock;  
  int n;

  //ソケットの生成
  sock = socket(AF_INET, SOCK_STREAM, 0);

  //接続先構造体の準備
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);

  //jokerのIPアドレス
  inet_pton(AF_INET, "160.12.172.5",  &server.sin_addr.s_addr);

  //サーバに接続
  connect(sock, (struct sockaddr *) &server, sizeof(server));

  //サーバからデータを受信
  memset(buf, 0, sizeof(buf));
  n = recv(sock, buf, sizeof(buf),0);

  //socketの終了
  close(sock);
}





int main(){
  char BUF[5];
  recv_func(BUF);
  printf("%s",BUF);
  return 0;
}
