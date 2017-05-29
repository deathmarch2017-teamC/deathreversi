#include"socket.h"

bool set_socket(char* ip_addr, int port){
  struct sockaddr_in server;

  //ソケットの生成
  serverSock = socket(AF_INET, SOCK_STREAM, 0);

  //接続先構造体の準備
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  //jokerのIPアドレス
  inet_pton(AF_INET, ip_addr,  &server.sin_addr.s_addr);

  //サーバに接続
  if(connect(serverSock, (struct sockaddr *) &server, sizeof(server))<-1){
    //perror("connect error\n");
    return false;
  }
  
  return true;
}


//送信する関数
bool send_func(char* buf){

  //送信
  if(send(sock,buf, strlen(buf),0)<0){
    //perror("send error\n");
    return false;
  }

  return true;
}

//受信する関数
bool recv_func(char* buf){
  //サーバからデータを受信
  //memset(buf, 0, sizeof(buf));
  if(recv(sock, buf, strlen(buf),0)<0){
    //perror("recv error\n");
    return false;
  }

  return true;
}
