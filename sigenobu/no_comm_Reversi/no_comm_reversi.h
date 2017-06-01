#ifndef NO_COMM_REVERSI_H
#define NO_COMM_REVERSI_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <string.h>

//wata
#include <string>
#include <unistd.h>
#include <iostream>


#include "GameMaster.h"
#include "Board.h"
#include "Reversi_AI.h"


void move_gen(char* move, int x, int y, int flag);
ostream& operator<<(ostream& os, const Point& p);
void assign_stringtochar(string input, char *output);
void assign_chartostring(char *input, string &output);
void assign_char(char *input, char *output);
int GFprocess(ConsoleBoard &board);
int against_rules(Color current_color);
bool attack_chance(int current_color, ConsoleBoard &board, string premove);
int abvsab(int* eval1, int* eval2);

#endif
