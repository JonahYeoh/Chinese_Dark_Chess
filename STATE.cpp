#include "STATE.h"
#include "ACTION.h"
State::State()
{
	memset( board, 0, 32 );
}

State::State(const State & s )
{
	setBoard( s.board );
	color = s.color;
	setCloseBoard( s.closeBoard );
}

State::~State( void ) { /*free(board);*/ }

void State::setBoard( const int src[32] )
{
	for ( int i = 0; i < 32; i++ ) board[i] = src[i];	
}

void State::setCloseBoard( const int src[14] )
{
	for ( int i = 0; i < 14; i++ ) closeBoard[i] = src[i];
}

list<Action> State::getChilds()
{
	list<Action> childs;
	list<Action> elist, mlist;
	const int power[7] = { 2, 3, 4, 5, 6, 7, 8 };
	// lamda expression
	auto check_surrounding = [&] ( int me, int r, int c, int i, int j, int clr )
				{
					Action action;
					int *m = (int*)malloc(sizeof(int)*2); memset( m, 0, 2 * sizeof( int ) );
					m[0] = r * 4 + c, m[1] = i * 4 + j;
					int adj_index = i * 4 + j;
					int adj_color = board[adj_index] / 7;
					int adj_type = board[adj_index] % 7;
					int adj_power = power[adj_type];
					if ( board[adj_index] == -2 ) // blank
					{
						// action.setType( 'M' );
						action.setReward( me );// 
						action.setAction( m );
						mlist.push_back( action );
					}
					else if ( board[adj_index] != -1 ) // not cover
					{
						if ( me - adj_power >= 0 ) // eatable
						{
							if ( clr != adj_color ) // is enermy
							{
								// action.setType( 'E' );
								action.setReward( me * adj_power );
								action.setAction( m );
								elist.push_back( action );
							}
						}
						else if ( me == 2 && adj_power == 8 && clr != adj_color )
						{
							// action.setType( 'E' );
							action.setReward( adj_power * adj_power );
							action.setAction( m );
							elist.push_back( action );
						}
					}
					free(m);
				};

	for ( int r = 0; r < 8; r++ )
	{
		for ( int c = 0; c < 4; c++ )
		{
			int index = r * 4 + c;
			int chess_color = board[index] / 7;
			int chess_type = board[index] % 7;
			int chess_power = power[chess_type];
			if ( board[index] == -2 || board[index] == -1 )
				continue;
			else if ( chess_type == 1 && color == chess_color )
			{
				int cannon_row, cannon_column; bool arch = false;
				int *m = (int*)malloc(sizeof( int ) * 2 ); memset( m, 0, 2 * sizeof( int ) );
				m[0] = r * 4 + c;
				if ( r >= 2 )
				{
					for ( cannon_row = r - 1; cannon_row >= 0; cannon_row-- ) // cannon up
					{
						int target = cannon_row * 4 + c;
						if ( board[target] != -2 && !arch )
						{
							arch = true;
						}
						else if ( arch && ( board[target] == -1 || ( board[target] / 7 ) == color ) )
						{
							break; // failed to attack
						}
						else if ( arch && board[target] != -2 && ( board[target] / 7 ) != color )
						{
							m[1] = target;
							Action action;
							// action.setType( 'E' );
							action.setReward( power[board[target]%7] * power[board[target]%7] );
							action.setAction( m );
							elist.push_back( action );
							break;
						}
					}
				}
				if ( r <= 5 )
				{
					arch = false;
					for ( cannon_row = r + 1; cannon_row < 8; cannon_row++ ) // cannon down
					{
						int target = cannon_row * 4 + c;
						if ( board[target] != -2 && !arch )
						{
							arch = true;
						}
						else if ( arch && ( board[target] == -1 || ( board[target] / 7 ) == color ) )
						{
							break; // failed to attack
						}
						else if ( arch && board[target] != -2 && ( board[target] / 7 ) != color )
						{
							m[1] = target;
							Action action;
							// action.setType( 'E' );
							action.setReward( power[board[target]%7] * power[board[target]%7] );
							action.setAction( m );
							elist.push_back( action );
							break;
						}
					}
				}
				if ( c != 3 )
				{
					arch = false; 
					for ( cannon_column = c + 1; cannon_column < 4; cannon_column++ ) // cannon right
					{
						int target = r * 4 + cannon_column;
						if ( board[target] != -2 && !arch )
						{
							arch = true;
						}
						else if ( arch && ( board[target] == -1 || ( board[target] / 7 ) == color ) )
						{
							break; // failed to attack
						}
						else if ( arch && board[target] != -2 && ( board[target] / 7 ) != color )
						{
							m[1] = target;
							Action action;
							// action.setType( 'E' );
							action.setReward( power[board[target]%7] * power[board[target]%7] );
							action.setAction( m );
							elist.push_back( action );
							break;
						}
					}
				}
				if ( c >= 2 )
				{
					arch = false;
					for ( cannon_column = c - 1; cannon_column >= 0; cannon_column-- ) // cannon left
					{
						int target = r * 4 + cannon_column;
						if ( board[target] != -2 && !arch )
						{
							arch = true;
						}
						else if ( arch && ( board[target] == -1 || ( board[target] / 7 ) == color ) )
						{
							break; // failed to attack
						}
						else if ( arch && board[target] != -2 && ( board[target] / 7 ) != color )
						{
							m[1] = target;
							Action action;
							// action.setType( 'E' );
							action.setReward( power[board[target]%7] * power[board[target]%7] );
							action.setAction( m );
							elist.push_back( action );
							break;
						}
					}
				}
				free(m);
			}
			else if ( chess_type == 6 && color == chess_color ) // k
			{
				if ( c + 1 < 4 && ( board[r*4+c+1] % 7 ) != 0 )		check_surrounding( chess_power, r, c, r, c+1, color );
				if ( c - 1 >= 0 && ( board[r*4+c-1] % 7 ) != 0 )	check_surrounding( chess_power, r, c, r, c-1, color );
				if ( r + 1 < 8 && ( board[(r+1)*4+c] % 7 ) != 0 )	check_surrounding( chess_power, r, c, r+1, c, color );
				if ( r - 1 >= 0 && ( board[(r-1)*4+c] % 7 ) != 0 ) 	check_surrounding( chess_power, r, c, r-1, c, color );
			}
			else if ( chess_type != 6 && color == chess_color ) // n
			{
				if ( c + 1 < 4 )	check_surrounding( chess_power, r, c, r, c+1, color );
				if ( c - 1 >= 0 )	check_surrounding( chess_power, r, c, r, c-1, color );
				if ( r + 1 < 8 )	check_surrounding( chess_power, r, c, r+1, c, color );
				if ( r - 1 >= 0 ) 	check_surrounding( chess_power, r, c, r-1, c, color );
			}
		}
	}
	elist.sort([]( const Action & act1, const Action & act2 ){
		if ( act1.reward== act2.reward ) return false;
        return act1.reward < act2.reward;	
	});
	mlist.sort([]( const Action & act1, const Action & act2 ){
		if ( act1.reward == act2.reward ) return false;
        return act1.reward < act2.reward;	
	});
	childs.splice( childs.begin(), elist );
	childs.splice( childs.begin(), mlist );
	return childs;
}

void State::switchColor()
{
	color = ( color == 0 ) ? 1 : 0;
}

int State::getColor(){	return color; }

void State::setColor( const int c ) { color = c; }

void State::walkover( int mov[2] )
{
	if ( board[mov[1]] != -1 && board[mov[1]] != -2 )
	{
		const int mapping[7] = { 6, 5, 4, 3, 2, 1, 0 };
		int index = mapping[board[mov[1]] % 7];
		int clr = board[mov[1]] / 7;
		if ( clr == 1 ) index += 7;
		closeBoard[index] -= 1;
	}
	char piece = board[mov[0]];
	board[mov[0]] = '-';
	board[mov[1]] = piece;
}

void State::getBoard( int dst[32] )
{
	for ( int i = 0; i < 32; i++ )
		dst[i] = board[i];
}
void State::getCloseBoard( int dst[14] )
{
	for ( int i = 0; i < 14; i++ )
		dst[i] = closeBoard[i];
}
// Referee
bool State::Referee(int* chess,int from_location_no,int to_location_no,int UserId)
{
	int MessageNo = 0;
	bool IsCurrent = true;
	int from_chess_no = chess[from_location_no];
	int to_chess_no = chess[to_location_no];
	int from_row = from_location_no / 4;
	int to_row = to_location_no / 4;
	int from_col = from_location_no % 4;
	int to_col = to_location_no % 4;

	if(from_chess_no < 0 || ( to_chess_no < 0 && to_chess_no != CHESS_EMPTY) )
	{  
		MessageNo = 1;
		//strcat(Message,"**no chess can move**");
		//strcat(Message,"**can't move darkchess**");
		IsCurrent = false;
	}
	else if (from_chess_no >= 0 && from_chess_no / 7 != UserId)
	{
		MessageNo = 2;
		//strcat(Message,"**not my chess**");
		IsCurrent = false;
	}
	else if((from_chess_no / 7 == to_chess_no / 7) && to_chess_no >= 0)
	{
		MessageNo = 3;
		//strcat(Message,"**can't eat my self**");
		IsCurrent = false;
	}
	//check attack
	else if(to_chess_no == CHESS_EMPTY && abs(from_row-to_row) + abs(from_col-to_col)  == 1)//legal move
	{
		IsCurrent = true;
	}	
	else if(from_chess_no % 7 == 1 ) //judge gun
	{
		int row_gap = from_row-to_row;
		int col_gap = from_col-to_col;
		int between_Count = 0;
		//slant
		if(from_row-to_row == 0 || from_col-to_col == 0)
		{
			//row
			if(row_gap == 0) 
			{
				for(int i=1;i<abs(col_gap);i++)
				{
					int between_chess;
					if(col_gap>0)
						between_chess = chess[from_location_no-i] ;
					else
						between_chess = chess[from_location_no+i] ;
					if(between_chess != CHESS_EMPTY)
						between_Count++;
				}
			}
			//column
			else
			{
				for(int i=1;i<abs(row_gap);i++)
				{
					int between_chess;
					if(row_gap > 0)
						between_chess = chess[from_location_no-4*i] ;
					else
						between_chess = chess[from_location_no+4*i] ;
					if(between_chess != CHESS_EMPTY)
						between_Count++;
				}
				
			}
			
			if(between_Count != 1 )
			{
				MessageNo = 4;
				//strcat(Message,"**gun can't eat opp without between one piece**");
				IsCurrent = false;
			}
			else if(to_chess_no == CHESS_EMPTY)
			{
				MessageNo = 5;
				//strcat(Message,"**gun can't eat opp without between one piece**");
				IsCurrent = false;
			}
		}
		//slide
		else
		{
			MessageNo = 6;
			//strcat(Message,"**cant slide**");
			IsCurrent = false;
		}
	}
	else // non gun
	{
		//judge pawn or king

		//distance
		if( abs(from_row-to_row) + abs(from_col-to_col)  > 1)
		{
			MessageNo = 7;
			//strcat(Message,"**cant eat**");
			IsCurrent = false;
		}
		//judge pawn
		else if(from_chess_no % 7 == 0)
		{
			if(to_chess_no % 7 != 0 && to_chess_no % 7 != 6)
			{
				MessageNo = 8;
				//strcat(Message,"**pawn only eat pawn and king**");
				IsCurrent = false;
			}
		}
		//judge king
		else if(from_chess_no % 7 == 6 && to_chess_no % 7 == 0)
		{
			MessageNo = 9;
			//strcat(Message,"**king can't eat pawn**");
			IsCurrent = false;
		}
		else if(from_chess_no % 7 < to_chess_no% 7)
		{
			MessageNo = 10;
			//strcat(Message,"**cant eat**");
			IsCurrent = false;
		}
	}
	return IsCurrent;
}

int State::Expand(int* Board,int color,int *Result) // []
{
	int ResultCount = 0;
	for(int i=0;i<32;i++)
	{
		if(Board[i] >= 0 && Board[i]/7 == color)
		{
			//Gun
			if(Board[i] % 7 == 1)
			{
				int row = i/4;
				int col = i%4;
				for(int rowCount=row*4;rowCount<(row+1)*4;rowCount++)
				{
					if(Referee(Board,i,rowCount,color))
					{
						Result[ResultCount] = i*100+rowCount;
						ResultCount++;
					}
				}
				for(int colCount=col; colCount<32;colCount += 4)
				{
				
					if(Referee(Board,i,colCount,color))
					{
						Result[ResultCount] = i*100+colCount;
						ResultCount++;
					}
				}
			}
			else
			{
				int Move[4] = {i-4,i+1,i+4,i-1};
				for(int k=0; k<4;k++)
				{
					
					if(Move[k] >= 0 && Move[k] < 32 && Referee(Board,i,Move[k],color))
					{
						Result[ResultCount] = i*100+Move[k];
						ResultCount++;
					}
				}
			}
		
		};
	}
	return ResultCount;
}

list<Action> State::getChilds2()
{
	list<Action> childs;
	list<Action> elist, mlist;
	const int power[7] = { 2, 3, 4, 5, 6, 7, 8 };
	
	int * result = (int*)malloc(sizeof(int)*100); 	memset( result, 0, sizeof(int)*100);
	int count = Expand( this->board, color, result );
	
	for ( int seq = 0; seq < count; seq++ )
	{
		int loc = result[seq];
		Action action;
		int self = this->board[loc/100], opo = this->board[loc%100];
		int m[2] = { loc/100, loc%100 };
		action.setAction( m );
		if ( this->board[loc%100] == -2 ) // moves
		{
			action.setReward(8 - power[self%7]);
			mlist.push_back( action );
		}
		else if ( self % 7 == 1 || ( self % 7 == 0 && opo % 7 == 6 ) ) // cannon || pawn vs king
		{
			action.setReward( power[opo%7]*power[opo%7] );
			elist.push_back( action );
		}
		else // others
		{
			action.setReward( power[self%7]*power[opo%7] );
			elist.push_back( action );	
		}
	}
	free( result );
	elist.sort([]( const Action & act1, const Action & act2 ){
		if ( act1.reward== act2.reward ) return false;
        return act1.reward < act2.reward;	
	});
	mlist.sort([]( const Action & act1, const Action & act2 ){
		if ( act1.reward == act2.reward ) return false;
        return act1.reward < act2.reward;	
	});
	childs.splice( childs.begin(), elist );
	childs.splice( childs.begin(), mlist );
	
	return childs;
}

