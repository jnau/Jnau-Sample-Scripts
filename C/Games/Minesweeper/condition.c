#ifndef PLAY_GAME_H
#define PLAY_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "mine_board.h"


//create a function to count how many "!" are there in the board, so it can be used for winning condition check
int umine_num(Mine pBoard){
	int i,j;
	int k=0;

	for(i=0;i<pBoard.row;++i){
		for(j=0;j<pBoard.col;++j){
			if(pBoard.graph[i][j]=='!'){
				++k;
			}
		}
	}

	return k;
}

//if the input is outside of the board, or, the tile is taken, return false
bool play_valid(Mine aBoard,Mine pBoard,int urow,int ucol){
	
	if(urow<0 || urow>(pBoard.row-2) || ucol<0 || ucol>(pBoard.col-2)){
		return false;
	}
	else{
		if(isdigit(pBoard.graph[pBoard.row-urow-2][ucol+1])){
			printf("This tile is already revealed.\n");
			return false;
		}
		else{
			return true;
		}
	}
}


//if reveal a mine, game over!!!!!!
bool game_over(Mine pBoard,int urow,int ucol){
	
	if(pBoard.graph[pBoard.row-urow-2][ucol+1]=='*'){
		return true;
	}
	else{
		return false;
	}
}


//if all tiles are revealed, and, no "?", all "!" = number of mines
bool game_won(Mine pBoard,Mine aBoard,int umine){

	int i,j;
	int k=0;
	int l=0;		
		
	
	if(umine!=pBoard.numMines){
		return false;
	}
	
	else if(umine==pBoard.numMines){
		
		for(i=0;i<pBoard.row;++i){
			for(j=0;j<pBoard.col;++j){
				if(pBoard.graph[i][j]=='!' && aBoard.graph[i][j]=='*'){
					++k;
				}
				if(pBoard.graph[i][j]=='#'){
					++l;
				}
				if(pBoard.graph[i][j]=='?'){
					return false;
				}
			}
		}

		//if haven found any #"
		if(k==pBoard.numMines && l==0){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
	
}

	
#endif	

