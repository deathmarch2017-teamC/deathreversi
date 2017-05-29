#include <stdio.h>
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

int main(){

  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  int len;
  int sock;

  //ソケットの作成
  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  //ソケットの設定
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(sock0, (struct sockaddr *) &addr, sizeof(addr));

  //TCPクライアントから接続要求を待機
  listen(sock0, 5);

  //TCPクライアントから接続要求を受ける
  printf("wait accept...\n");
  len = sizeof(client);
  sock = accept(sock0, (struct sockaddr *) &client, (socklen_t *)&len);

  printf("accept complete!\n");
  //送信
  write(sock0, "A", 1);

  //TCPセッション終了
  close(sock);

  //listen するSocketの終了
  close(sock0);

  return 0;
}
