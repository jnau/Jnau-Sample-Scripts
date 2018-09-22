#ifndef DOARD_H
#define DOARD_H
#include <stdio.h>
#include <stdbool.h>

void create_board(int rows,int columns,int** A);
void print_board(int rows,int columns, int** A);
void destroy_board(int rows,int columns,int** A);
void play_game(int rows,int columns,int numForWin,int** A);
int play_valid(int userInput,int rows,int columns,int**A);
bool game_over(int rows,int columns,int** A);
bool game_won(int rows,int columns,int userNum,int numForWin,int** A);
bool row_win(int rows,int columns,int userAlpha,int numForWin,int** A);
bool column_win(int rows,int columns,int userAlpha,int numForWin,int** A);
bool diag_win(int rows,int columns,int userAlpha,int numForWin,int** A);
bool rightdiag_win(int rows,int columns,int userAlpha,int numForWin,int** A);


#endif
		
