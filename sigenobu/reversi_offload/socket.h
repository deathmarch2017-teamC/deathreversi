#ifndef SOCKET_H
#define SOCKET_H
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

int set_socket_connect(char* ip_addr, int port);
int set_socket_accept(char* ip_addr, int port);
bool send_func(int dstSock, char* BUF);
bool recv_func(int dstSock, char* BUF);
int close_socket(int dstSock);
#endif
