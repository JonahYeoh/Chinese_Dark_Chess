#ifndef STATE_INCLUDED
#define STATE_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <list>

#include "ACTION.h"

#define RED 0
#define BLACK 1
#define CHESS_COVER -1
#define CHESS_EMPTY -2
#define COMMAND_NUM 18

using namespace std;

class State{
	public:
		State(); // Default Constructor
		State( const State & s ); // Copy Constructor
		~State(void); // destructor
		void setBoard( const int src[32] ); // most likely not gonna use
		void setCloseBoard( const int src[14] );
		void getCloseBoard( int dst[14] );
		list<Action> getChilds();
		list<Action> getChilds2(); // improved version
		void switchColor();
		int getColor();
		void setColor( const int c );
		void walkover( int mov[2] );
		void getBoard( int dst[32] );
	private:
		int color;
		int board[32];
		int closeBoard[32];
		bool Referee(int* chess,int from_location_no,int to_location_no,int UserId);
		int Expand(int* Board,int color,int *Result);
};

#endif

