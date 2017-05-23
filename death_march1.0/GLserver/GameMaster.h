#ifndef GAME_MASTER_H
#define GAME_MASTER_H

#include <iostream>
#include <stdio.h>
//#include "../Board.h"
//change watanabe 2017/3/30
#include "Board.h"
#include <sysexits.h>

#include <cstdlib>



using namespace std;



class ConsoleBoard : public Board
{
public:
void print()
	{
	  cout << "    a b c d e f g h i j k l " << endl;
	  for(int y=1; y<=BOARD_SIZE; y++)
	    {
	      if(y<10){
		cout << " 0" <<dec<< y;
	      }
	      else{
		    cout <<" "<<dec<<y;
	      }
	      for(int x=1; x<=BOARD_SIZE; x++)
		{
		  switch(getColor(Point(x, y)))
				{
				case BLACK:
				  cout << " B";
				  break;
				case WHITE:
				  cout << " W";
				  break;
				case WALL:
				  cout << " #";
				  break;
				default:
					cout << "  ";
					break;
				}
		}
	      cout << endl;
	    }
	}
};




#endif
