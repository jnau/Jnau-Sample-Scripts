#ifndef MINE_H
#define MINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct Mine_struct{
	int col;
	int row;
	int numMines;
	int rand_seed;
	int** graph;
	bool** status;

} Mine;

void create_play_board(Mine board);
void create_answer_board(Mine board);
void print_board(Mine board);
void destroy_board(Mine board);
void play_game(Mine aBoard,Mine pBoard);
bool play_valid(Mine aBoard,Mine pBoard,int urow,int ucol);
bool game_over(Mine pBoard,int urow,int ucol);
void reveal(Mine aboard, Mine pboard, int row, int col);
int umine_num(Mine pBoard);
bool game_won(Mine pBoard,Mine aBoard,int umine);



#endif
