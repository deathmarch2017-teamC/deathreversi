#ifndef CLIENT_ROUTINE_H
#define CLIENT_ROUTINE_H

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<string.h>
#include"GameMaster.h"
#include"Board.h"
#include"Reversi.h"
#include"socket.h"
#include"Reversi_AI.h"
#define DATASIZE 4
//extern int serverSock;

using namespace std;

int setting_game(int &dstSock, char* teamname);
int board_update(int &dstSock, Board &board);
void move_gen(char* move, int x, int y, int flag);

#endif
