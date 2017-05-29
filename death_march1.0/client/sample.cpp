#include <stdio.h>
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

int main(){
  struct sockaddr_in server;
  int sock;  
  char buf[32];
  int n;

  //ソケットの生成
  sock = socket(AF_INET, SOCK_STREAM, 0);

  //接続先構造体の準備
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);

  inet_pton(AF_INET, "160.12.172.5",  &server.sin_addr.s_addr);

  //サーバに接続
  connect(sock, (struct sockaddr *) &server, sizeof(server));

  //サーバからデータを受信
  memset(buf, 0, sizeof(buf));
  n = read(sock, buf, sizeof(buf));

  printf("%d,%s",n, buf);

  //socketの終了
  close(sock);

  printf("%d,%s",n, buf);

  return 0;
}
