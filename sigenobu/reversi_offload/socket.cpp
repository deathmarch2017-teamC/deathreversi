#include"socket.h"
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
    dstSockaddr.sin_port = htons(port);
    dstSockaddr.sin_family = AF_INET;
    dstSockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    dstSock = socket(AF_INET, SOCK_STREAM, 0);
    
    bind(dstSock, (struct sockaddr *) &dstSockaddr, sizeof(dstSockaddr));

    listen(dstSock, 1);
    std::cout << "port: " << port << " wait connection ..." << std::endl;
    if(dstSock = accept(dstSock, (struct sockaddr *) &dstSockaddr, (socklen_t *)sizeof(dstSockaddr)) < -1){
      std::cout << "not connect" << std::endl;
      return false;
    }
    printf("connected %s\n", inet_ntoa(dstSockaddr.sin_addr));
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
